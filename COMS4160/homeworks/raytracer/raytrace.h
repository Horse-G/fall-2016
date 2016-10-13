// Filename:    raytrace.h
// Author:      Adam Hadar, anh2130
// Purpose:     The actual raytracing routine for a simple raytracer.
// Edited:      2016-10-13

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
        s_clr_color i_clr;
        s_material  i_mat;

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

        // generate data II
        i_mat = *scene._materials[i_sct.get_material()];
        
        // APPLY SHADING
        // I originally had separate functions, but I feel like a function
        //   call for each pixel might be too much, so I inlined shading.
        // The default is to run blinn-phong, but you can compile with
        //   assn1's simple if you want, by using the additional compile
        //   directive: `-D SHADING=1`.
        // I wrote up a cel-shading that works somewhat as defined in 10-3,
        //   with compile directive: `-D SHADING=2`. I can't make lines
        //   between surfaces b/c we haven't computed their intersections
        //   yet.
        #ifndef SHADING
        {
            // memory allocation
            t_scalar     shading_dist, shading_scale_diff, shading_scale_spec;
            s_geo_vector shading_vec, shading_l, shading_v, shading_h;

            i_clr = scene._light_ambient.get_color() * i_mat.get_diff();
            // point lights
            for(z = 0; z < scene._lights_point.size(); ++z)
            {
                shading_vec = i_sct.get_point() - scene._lights_point[z]->get_point();
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

                i_clr += scene._lights_point[z]->get_color() * (
                    // diffuse
                    i_mat.get_diff()*shading_scale_diff
                    // specular
                    + i_mat.get_spec()*pow(shading_scale_spec, i_mat.get_phng()) //* shading_dist
                ) * shading_dist;
            }
        }
        // assn01-shading
        #elif SHADING==1
        {
            i_clr = scene.light_ambient.get_color() + i_mat.get_diff();
        }
        // cel-shading
        #elif SHADING==2
        {
            // memory allocation
            t_scalar     shading_scale_k, shading_dist;
            s_geo_vector shading_vec, shading_l, shading_v, shading_h;

            s_clr_color clr_warm, clr_cold;
            clr_warm = s_clr_color(0.4,0.4,0.7);
            clr_cold = s_clr_color(0.8,0.6,0.6);

            i_clr = scene._light_ambient.get_color() * i_mat.get_diff();
            for(z = 0; z < scene._lights_point.size(); ++z)
            {
                shading_vec = i_sct.get_point() - scene._lights_point[z]->get_point();
                shading_dist = 8000. / pow(shading_vec.len(),2.0);
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
                    i_clr = s_clr_color(0.0,0.0,0.0);
                // dark gray for borders
                else if((i_sct.get_surf_type() != PLANE && i_sct.get_normal() % shading_v <= 0.3))
                    i_clr = s_clr_color(0.05,0.05,0.05);
                // cool2warm everywhere else
                else
                    i_clr += clr_cold + (clr_warm - clr_cold)*shading_scale_k;
            }
        }
        #endif
        
        // STORE COLOR
        i_pxl->r = i_clr.get_r();
        i_pxl->g = i_clr.get_g();
        i_pxl->b = i_clr.get_b();
        i_pxl->a = 1.0;
    }
    
    return;
}

//// EOF ////
