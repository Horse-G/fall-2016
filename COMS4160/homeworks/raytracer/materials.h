// Filename:    materials.h
// Author:      Adam Hadar, anh2130
// Purpose:     Definitions for materials in a simple raytracer.
// Edited:      2016-10-23

//************************************************************************
// MATERIAL
//************************************************************************
class c_material
{
    public:
    // subclass destructor
    virtual ~c_material(void){}
    
    // subclass compute shading
    virtual s_spd_radiance compute_shading(const s_intersect&, const s_geo_ray&, // const s_scene&) = 0;
            const c_light_ambient&, const std::vector<c_light_point*>&, const std::vector<c_surface*>&) = 0;
};

//************************************************************************
// MATERIAL_DEFAULT
//************************************************************************
class c_mat_default: public c_material
{
    private:
    s_spd_radiance _diff;
    
    public:
    // constructors
    c_mat_default(void){}
    c_mat_default(const s_spd_radiance& spdr): _diff(spdr) {}
    
    // inherited destructor
    virtual ~c_mat_default(void){}

    // get contents
    s_spd_radiance get_diff(void) const
    {
        return _diff;
    }

    // inherited compute shading
    virtual s_spd_radiance compute_shading(const s_intersect& i_sct, const s_geo_ray& i_ray, // const s_scene& sc)
            const c_light_ambient& ambient, const std::vector<c_light_point*>& lights_point, const std::vector<c_surface*>& surfaces)
    {
        return _diff;
    }
};

//************************************************************************
// MATERIAL_BLINN_PHONG
//************************************************************************
class c_mat_blinn_phong: public c_material
{
    private:
    s_spd_radiance _diff, _spec;
    t_scalar       _phng;
    s_geo_vector   _refl;
    
    public:
    // constructors
    c_mat_blinn_phong(void){}
    c_mat_blinn_phong(const s_spd_radiance& spdr1, const s_spd_radiance& spdr2, const t_scalar& s, const s_geo_vector& gv):
        _diff(spdr1),
        _spec(spdr2),
        _phng(s),
        _refl(gv){}

    // inherited destructor
    virtual ~c_mat_blinn_phong(void){}

    // get contents
    s_spd_radiance get_diff(void) const
    {
        return _diff;
    }
    s_spd_radiance get_spec(void) const
    {
        return _spec;
    }
    t_scalar get_phng(void) const
    {
        return _phng;
    }
    s_geo_vector get_refl(void) const
    {
        return _refl;
    }

    // inherited compute shading
    virtual s_spd_radiance compute_shading(const s_intersect& i_sct, const s_geo_ray& i_ray, // const s_scene& sc)
            const c_light_ambient& ambient, const std::vector<c_light_point*>& lights_point, const std::vector<c_surface*>& surfaces)
    {
        // memory allocation
        t_scalar       shading_dist,
                       shading_scale_diff,
                       shading_scale_spec,
                       i, j;
        s_geo_vector   shading_vec,
                       shading_l,
                       shading_v,
                       shading_h;
        s_spd_radiance intensity,
                       i_clr;
        s_geo_ray      shadow_ray;
        s_intersect    shadow_sct;
        
        // ambient component
        i_clr = ambient.get_radiance() * _diff;

        for(i = 0; i < lights_point.size(); ++i)
        {
            // find if it is being blocked
            s_geo_vector vec_to_light = lights_point[i]->get_point() - i_sct.get_point();
            
            shadow_ray = s_geo_ray(i_sct.get_point(), 
                    vec_to_light);
            shadow_sct = s_intersect();
            
            for(j = 0; j < surfaces.size(); ++j)
            {
                shadow_sct = surfaces[j]->is_intersect(shadow_ray);
                if(shadow_sct.get_is_true()
                && shadow_sct.get_t() > EP_SHADOW
                //&& shadow_sct.get_t() < vec_to_light.len()
                )
                    break;
            }
            if(shadow_sct.get_is_true() == false)
            {
                shading_vec = i_sct.get_point() - lights_point[i]->get_point();
                shading_dist = 1. / pow(shading_vec.len(), 2.0);
                shading_l = shading_vec.norm();
                shading_v = (i_sct.get_point() - i_ray.get_origin()).norm();
                shading_h = (shading_l + shading_v).norm();
                
                // diffuse component
                shading_scale_diff = i_sct.get_normal() % shading_l;
                if(shading_scale_diff < 0.0)
                    shading_scale_diff = 0.0;
                // specular component
                shading_scale_spec = i_sct.get_normal() % shading_h;
                if(shading_scale_spec < 0.0)
                    shading_scale_spec = 0.0;
                
                i_clr += lights_point[i]->get_radiance() * (
                    // diffuse
                    _diff * shading_scale_diff
                    // specular
                    + _spec * pow(shading_scale_spec, _phng)
                    ) * shading_dist;
            }
        }
        return i_clr;
    }
};

//************************************************************************
// MATERIAL_CELL_SHADED
//************************************************************************
class c_mat_cell_shaded: public c_material
{
    private:
    s_spd_radiance _diff;
    
    public:
    // constructors
    c_mat_cell_shaded(void){}
    c_mat_cell_shaded(const s_spd_radiance& spdr): _diff(spdr){}
    
    // inherited destructor
    ~c_mat_cell_shaded(void){}

    // get contents
    s_spd_radiance get_diff(void) const
    {
        return _diff;
    }

    // inherited compute_shading
    virtual s_spd_radiance compute_shading(const s_intersect& i_sct, const s_geo_ray& i_ray, // const s_scene& sc)
            const c_light_ambient& ambient, const std::vector<c_light_point*>& lights_point, const std::vector<c_surface*>& surfaces)
    {
        // memory allocation
        t_scalar       shading_scale_k, shading_dist;
        s_geo_vector   shading_vec, shading_l, shading_v, shading_h;
        s_spd_radiance i_clr, clr_warm, clr_cold;
        t_uint i;

        clr_warm = s_spd_radiance(0.4,0.4,0.7);
        clr_cold = s_spd_radiance(0.8,0.6,0.6);
        i_clr = ambient.get_radiance() * _diff;
        
        for(i = 0; i < lights_point.size(); ++i)
        {
            shading_vec = i_sct.get_point() - lights_point[i]->get_point();
            shading_dist = 1. / pow(shading_vec.len(),2.0);
            shading_l = shading_vec.norm();
            shading_v = (i_sct.get_point() - i_ray.get_origin()).norm();
            shading_h = (shading_l + shading_v).norm();
            shading_scale_k = i_sct.get_normal() % shading_l;
            if(shading_scale_k < 0.0)
                shading_scale_k = 0.0;
            shading_scale_k *= shading_dist;
            shading_scale_k += 1.0;
            shading_scale_k /= 2.0;
            
            // black for nothingness
            if(i_sct.get_material() == 0)
                i_clr = s_spd_radiance(0.0,0.0,0.0);
            // dark gray for borders
            else if((i_sct.get_surf_type() != PLANE && i_sct.get_normal() % shading_v <= 0.3))
                i_clr = s_spd_radiance(0.05,0.05,0.05);
            // cool2warm everywhere else
            else
                i_clr += clr_cold + (clr_warm - clr_cold)*shading_scale_k;
        }
        return i_clr;
    }
};

//// EOF ////
