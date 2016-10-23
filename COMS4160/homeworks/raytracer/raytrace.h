// Filename:    raytrace.h
// Author:      Adam Hadar, anh2130
// Purpose:     The actual raytracing routine for a simple raytracer.
// Edited:      2016-10-23

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

        // APPLY SHADING
        i_clr = scene._materials[i_sct.get_material()]->
            compute_shading(i_sct, i_ray, // scene);
                    scene._light_ambient, scene._lights_point, scene._surfaces);
        
        // STORE COLOR
        i_pxl->r = i_clr.get_r();
        i_pxl->g = i_clr.get_g();
        i_pxl->b = i_clr.get_b();
        i_pxl->a = 1.0;
    }
    
    return;
}

//// EOF ////
