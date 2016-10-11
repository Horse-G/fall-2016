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
    s_geo_ray               i_ray;
    s_intersect             i_sct, ii_sct;
    s_clr_color             i_clr;
    Imf::Rgba*              i_pxl;
    s_material              i_mat;
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
    //scene.print_verbose();

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
        
        /* APPLYING SHADING
         *   - `simple`
         *   - `blinn_phong`
         */
        //shading_simple(
        shading_blinn_phong(
            i_clr,
            i_mat,
            i_sct,
            i_ray.get_origin(),
            scene.light_ambient.get_color(),
            scene.lights_point
        );
        
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
