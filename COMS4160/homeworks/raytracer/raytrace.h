// Filename:    raytrace.h
// Author:      Adam Hadar, anh2130
// Purpose:     The actual raytracing routine for a simple raytracer.
// Edited:      2016-10-27

//******************************************************************************
// SUBROUTINE_COMPUTE_L (recursive)
//******************************************************************************

// default - return _diff
// cell shaded
/*
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
 */
s_spd_radiance compute_L(const s_geo_ray& i_ray, const s_scene& sc, const t_uint& recurse_limit, const t_scalar& t_min, const t_scalar& t_max, const t_ray& ray_type, const c_light_point& thisLight)
{
    s_spd_radiance i_clr = s_spd_radiance(0.0,0.0,0.0);
    // if recurse_limit == 0, return [ 0 0 0 ]
    if (recurse_limit == 0)
        return i_clr;
    
    // memory allocation
    t_scalar    i;
    s_intersect i_sct, ii_sct;
    
    // if ray_type == SHADOW_RAY
    if(ray_type == SHADOW)
    {
        for(i = 0; i < sc._surfaces.size(); ++i)
        {
           i_sct = sc._surfaces[i]->is_intersect(i_ray);
           if(i_sct.get_is_true()
           && i_sct.get_t() > t_min
           && i_sct.get_t() < t_max)
               return i_clr;
        }
        return thisLight.get_radiance();
    }

    // get closest intersection
    i_sct = s_intersect(t_max);
    for(i = 0; i < sc._surfaces.size(); ++i)
    {
        ii_sct = sc._surfaces[i]->is_intersect(i_ray);
        if(ii_sct.get_is_true()
        && ii_sct.get_t() > t_min
        && ii_sct.get_t() < i_sct.get_t())
           i_sct = ii_sct;
    }
    // if there is no intersection
    if(i_sct.get_is_true() == false)
        return s_spd_radiance(0.0,0.0,0.0);

    // otherwise, allocate some memory
    s_geo_vector   shading_vec;
    s_spd_radiance intensity,
                   ii_clr;
    c_mat_blinn_phong* i_mat;

    i_mat = sc._materials[i_sct.get_material()];
    for(i = 0; i < sc._lights_point.size(); ++i)
    {
        // memory allocation
        s_geo_ray      shadow_ray;
        s_intersect    shadow_sct;

        // find if it is being blocked
        s_geo_vector vec_to_light = sc._lights_point[i]->get_point() - i_sct.get_point();
        shadow_ray = s_geo_ray(i_sct.get_point(),
                vec_to_light);
        shadow_sct = s_intersect();

        ii_clr = compute_L(shadow_ray, sc, 1, EP_SHADOW, vec_to_light.len(), SHADOW, *sc._lights_point[i]);
        if (ii_clr > 0.0)
        {
            // memory allocation
            t_scalar shading_dist, shading_scale_diff, shading_scale_spec;
            s_geo_vector shading_l, shading_v, shading_h;
            
            shading_vec = i_sct.get_point() - sc._lights_point[i]->get_point();
            shading_dist = 1. / pow(shading_vec.len(),2.0);
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

            i_clr += ii_clr * (
                i_mat->get_diff() * shading_scale_diff
                + i_mat->get_spec() * pow(shading_scale_spec, i_mat->get_phng())
                ) * shading_dist;
        }
    }
    // ambient component
    i_clr += sc._light_ambient.get_radiance() * i_mat->get_diff();
    
    if(i_mat->get_refl() > 0.0)
    {
        s_geo_ray ref_ray = s_geo_ray(i_sct.get_point(),
            i_ray.get_direction() - i_sct.get_normal() * 2.0 * (i_ray.get_direction() % i_sct.get_normal()));
        i_clr += i_mat->get_refl() * compute_L(ref_ray, sc, recurse_limit - 1, EP_REFL, std::numeric_limits<t_scalar>::infinity(), REFLECTION, c_light_point());
    }
    return i_clr;
}

//******************************************************************************
// SUBROUTINE_RAYTRACE_DO
//******************************************************************************
void raytrace_do(
        Imf::Array2D<Imf::Rgba>& img_pixels,
        // NOTE: I pass in v_px,v_py because I don't want to do those function calls again
        const t_scalar& v_px,
        const t_scalar& v_py,
        const s_scene& scene
)
{
    // memory allocation
    t_uint                  x, y, z,
                            v_ix, v_iy;
    t_scalar                d_x, d_y,
                            o_x, o_y,
                            v_fl;
    s_geo_point             v_eye;
    s_geo_vector            v_u, v_v, v_w;
    
    // in order to reduce function calls, I do all of them once, here
    v_eye = scene._viewports[0]->get_eye();
    v_u = scene._viewports[0]->get_u();
    v_v = scene._viewports[0]->get_v();
    v_w = scene._viewports[0]->get_w();
    v_fl = scene._viewports[0]->get_fl();
    v_ix = scene._viewports[0]->get_ix();
    v_iy = scene._viewports[0]->get_iy();

    // assigning to common constants
    d_x = v_ix/v_px;
    d_y = v_iy/v_py;
    o_x = 0.5 + v_px/2.0;
    o_y = 0.5 + v_py/2.0;
    
    // iterate through pixels
    for(y = 0; y < v_py; ++y)
    for(x = 0; x < v_px; ++x)
    {
        // memory allocation
        Imf::Rgba*  i_pxl;
        s_intersect i_sct, ii_sct;
        s_geo_ray   i_ray;
        s_spd_radiance i_clr;

        // generate data
        i_pxl = &img_pixels[y][x];
        i_sct = BLACKNESS;
        i_ray = s_geo_ray(v_eye,
              v_u * d_x * (x - o_x)
            + v_v * d_y * (o_y - y)
            - v_w * v_fl);
        
        // iterate through surfaces
        for(z = 0; z < scene._surfaces.size(); ++z)
        {
            ii_sct = scene._surfaces[z]->is_intersect(i_ray);
            // weeds out only the closest intersection, that is on the correct
            //   of the camera
            if(ii_sct.get_is_true()
                    && ii_sct.get_t() < i_sct.get_t() && ii_sct.get_t() > v_fl)
                i_sct = ii_sct;
        }

        i_clr = compute_L(i_ray, scene, 2, v_fl, std::numeric_limits<t_scalar>::infinity(), PRIMARY, c_light_point());

        // STORE COLOR
        i_pxl->r = i_clr.get_r();
        i_pxl->g = i_clr.get_g();
        i_pxl->b = i_clr.get_b();
        i_pxl->a = 1.0;
    }
    
    return;
}

//// EOF ////
