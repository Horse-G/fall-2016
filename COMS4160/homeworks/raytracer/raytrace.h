// Filename:    raytrace.h
// Author:      Adam Hadar, anh2130
// Purpose:     The actual raytracing routine for a simple raytracer.
// Edited:      2016-10-30

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
s_spd_radiance compute_L(
    const s_geo_ray& i_ray,
    const s_scene& sc,
    const t_uint& recurse_limit,
    const t_scalar& t_min, const t_scalar& t_max,
    const t_ray& ray_type,
    const c_light_point& thisLight)
{
    s_spd_radiance i_clr = s_spd_radiance(0.0,0.0,0.0);
    
    if (recurse_limit == 0)
        return i_clr;
    
    // memory allocation I
    t_scalar    i;
    s_intersect i_sct, ii_sct;
    
    switch(ray_type)
    {
        // SHADOW RAY
        case SHADOW:
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
       
        // EVERY OTHER RAY
        default:
        {
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
                return i_clr;

            // memory allocation II
            c_mat_blinn_phong* i_mat = sc._materials[i_sct.get_material()];
            
            // ambient component
            if(ray_type == PRIMARY)
                i_clr += sc._light_ambient.get_radiance() * i_mat->get_diff();
            
            for(i = 0; i < sc._lights_point.size(); ++i)
            {
                // memory allocation III
                s_geo_vector   shadow_vec = sc._lights_point[i]->get_point() - i_sct.get_point();
                s_spd_radiance ii_clr = compute_L(
                    s_geo_ray(i_sct.get_point(), shadow_vec),
                    sc,
                    1,
                    EP_SHADOW, shadow_vec.len(),
                    SHADOW,
                    *sc._lights_point[i]
                );
        
                if (ii_clr > 0.0)
                {
                    // memory allocation IV
                    s_geo_vector shading_l = -shadow_vec.norm();
                    s_geo_vector shading_v = (i_sct.get_point() - i_ray.get_origin()).norm();
                    t_scalar     shading_scale_diff = i_sct.get_normal() % shading_l;
                    t_scalar     shading_scale_spec = i_sct.get_normal() % (shading_l + shading_v).norm();
                    
                    ii_clr /= pow(shadow_vec.len(), 2.0);
                    
                    // diffuse component
                    if(shading_scale_diff > 0.0)
                        i_clr += ii_clr * i_mat->get_diff() * shading_scale_diff;
                    // specular component
                    if(shading_scale_spec > 0.0)
                        i_clr += ii_clr * i_mat->get_spec() * pow(shading_scale_spec, i_mat->get_phng());
                }
            }
    
            // reflection recursion
            if(i_mat->get_refl() > 0.0)
                i_clr += i_mat->get_refl()
                    * compute_L(
                        s_geo_ray(
                            i_sct.get_point(),
                            i_ray.get_direction() - i_sct.get_normal() * (2.0 * (i_ray.get_direction() % i_sct.get_normal()))
                        ),
                        sc,
                        recurse_limit - 1,
                        EP_REFL, std::numeric_limits<t_scalar>::infinity(),
                        REFLECTION,
                        c_light_point()
                    )
                ;
            return i_clr;
        }
    }
}

//******************************************************************************
// SUBROUTINE_RAYTRACE_DO
//******************************************************************************
void raytrace_do(
        Imf::Array2D<Imf::Rgba>& img_pixels,
        const t_scalar& px_start, const t_scalar& px_end,
        const t_scalar& py_start, const t_scalar& py_end,
        const s_scene&    scene,
        const c_viewport& viewport)
{
    // in order to reduce function calls, I do all of them once, here
    s_geo_point  v_eye = viewport.get_eye();
    s_geo_vector v_u   = viewport.get_u();
    s_geo_vector v_v   = viewport.get_v();
    s_geo_vector v_w   = viewport.get_w();
    t_scalar     v_fl  = viewport.get_fl();

    // pixel step, center of viewport
    t_scalar d_x = viewport.get_ix()/(px_end - px_start);
    t_scalar d_y = viewport.get_iy()/(py_end - py_start);
    t_scalar o_x = (px_end + px_start + 1.0)/2.0;
    t_scalar o_y = (py_end + py_start + 1.0)/2.0;
    
    // iterate through pixels
    for(t_uint y = py_start; y < py_end; ++y)
    for(t_uint x = px_start; x < px_end; ++x)
    {
        // generate data
        Imf::Rgba* i_pxl     = &img_pixels[y][x];
        s_spd_radiance i_clr = viewport.filter(
            compute_L(
                s_geo_ray(
                    v_eye,
                    v_u * d_x * (x - o_x)
                    + v_v * d_y * (o_y - y)
                    - v_w * v_fl
                ),
                scene,
                20,
                v_fl, std::numeric_limits<t_scalar>::infinity(),
                PRIMARY,
                c_light_point()
            )
        );
        // STORE COLOR
        i_pxl->r = i_clr.get_r();
        i_pxl->g = i_clr.get_g();
        i_pxl->b = i_clr.get_b();
        i_pxl->a = 1.0;
    }
    return;
}

//// EOF ////
