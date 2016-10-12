/*
 * Filename:    main.cc
 * Author:      Adam Hadar, anh2130
 * Purpose:     The main function for a simple raytracer.
 * Edited:      2016-10-11
 */

#include "common.h"

//************************************************************************
// ROUTINE_MAIN
//************************************************************************
int main(int argc, char **argv)
{
    if (argc != 3)
    {
        std::cerr
            <<"invalid usage of command: `" <<argv[0] <<"`" <<std::endl
            <<"correct usage: `" <<argv[0] <<" <input_file.scn> <output_file.exr>`" <<std::endl;
        return 1;
    }
    // try necessary for OpenEXR API
    try{
    // memory allocation
    Imf::Array2D<Imf::Rgba> img_pixels;
    s_scene                 scene;
    t_uint                  x, y, z,
                            v_ix, v_iy;
    t_scalar                d_x, d_y,
                            o_x, o_y,
                            v_fl,
                            v_px, v_py;
    s_geo_point             v_eye;
    s_geo_vector            v_u, v_v, v_w;
    
    // parse the scene filei
    io_input_scene(scene, argv[1]);
    // in order to reduce function calls, I do all of them once, here
    v_eye = scene.viewports[0]->get_eye();
    v_u = scene.viewports[0]->get_u();
    v_v = scene.viewports[0]->get_v();
    v_w = scene.viewports[0]->get_w();
    v_fl = scene.viewports[0]->get_fl();
    v_ix = scene.viewports[0]->get_ix();
    v_iy = scene.viewports[0]->get_iy();
    v_px = scene.viewports[0]->get_px();
    v_py = scene.viewports[0]->get_py();
    #ifdef PRINT
    io_print_scene_verbose();
    #endif

    // assigning to common constants
    d_x = v_ix/v_px;
    d_y = v_iy/v_py;
    o_x = 0.5 + v_px/2.0;
    o_y = 0.5 + v_py/2.0;
    
    // size image to scene specs
    img_pixels.resizeErase(v_py, v_px);
    
    // iterate through pixels
    for(y = 0; y < v_py; ++y)
    for(x = 0; x < v_px; ++x)
    {
        // memory allocated for each pixel
        Imf::Rgba*  i_pxl;
        s_intersect i_sct, ii_sct;
        s_geo_ray   i_ray;
        s_clr_color i_clr;
        s_material  i_mat;

        // generate pixel reference
        i_pxl = &img_pixels[y][x];
        // generate the default blackness
        i_sct = BLACKNESS;
        // generate ray
        i_ray = s_geo_ray(v_eye,
              v_u * d_x * (x - o_x)
            + v_v * d_y * (o_y - y)
            - v_w * v_fl);
        // iterate through surfaces
        for(z = 0; z < scene.surfaces.size(); ++z)
        {
            ii_sct = scene.surfaces[z]->is_intersect(i_ray);
            if(ii_sct.get_is_true() && ii_sct.get_t() < i_sct.get_t())
                i_sct = ii_sct;
        }

        // compute color
        i_mat = scene.materials[i_sct.get_material()];
        
        // APPLY SHADING
        /* 
         *   I originally had separate functions, but I feel like a function
         *     call for each pixel might be too much, so I inlined shading.
         *   The default is to run blinn-phong, but you can compile with
         *     assn1's simple if you want, by using the additional compile
         *     directive: `-D SHADING=1`.
         *   I wrote up a cel-shading that works somewhat as defined in 10-3,
         *      with compile directive: `-D SHADING=2`. I can't make lines
         *      between surfaces b/c we haven't computed their intersections
         *      yet.
         *   I've also scoped each section to make sure their temporary
         *     variables scope out after the computation.
         */
        #ifndef SHADING
        {
            t_scalar     shading_dist, shading_scale_diff, shading_scale_spec;
            s_geo_vector shading_vec, shading_l, shading_v, shading_h;

            i_clr = scene.light_ambient.get_color() * i_mat.get_diff();
            // point lights
            for(z = 0; z < scene.lights_point.size(); ++z)
            {
                shading_vec = i_sct.get_point() - scene.lights_point[z]->get_point();
                shading_dist = 8000. / pow(shading_vec.len(),2.0);
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

                i_clr += scene.lights_point[z]->get_color() * (
                    // diffuse
                    i_mat.get_diff()*shading_scale_diff
                    // specular
                    + i_mat.get_spec()*pow(shading_scale_spec, i_mat.get_phng()) //* shading_dist
                );
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
            t_scalar     shading_scale_k, shading_dist;
            s_geo_vector shading_vec, shading_l, shading_v, shading_h;

            s_clr_color clr_warm, clr_cold;
            clr_warm = s_clr_color(0.4,0.4,0.7);
            clr_cold = s_clr_color(0.8,0.6,0.6);

            i_clr = scene.light_ambient.get_color() * i_mat.get_diff();
            for(z = 0; z < scene.lights_point.size(); ++z)
            {
                shading_vec = i_sct.get_point() - scene.lights_point[z]->get_point();
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
    
    //write to file
    io_output_image(argv[2], img_pixels, v_px, v_py);
    }
    catch(const std::exception &e)
    {
        std::cerr <<"!EXCEPTION CAUGHT!" <<e.what() <<std::endl;
        return 1;
    }
    return 0;
}

//// EOF ////
