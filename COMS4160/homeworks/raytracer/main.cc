/*
 * Filename:    main.cc
 * Author:      Adam Hadar, anh2130
 * Purpose:     The main function for a simple raytracer.
 * Edited:      2016-10-06
 */

#include "h_common.h"

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
    s_scene scene;
    t_uint x,y,z;
    t_scalar d_x, d_y, o_x, o_y;
    s_geo_ray    i_ray;
    t_uint which_sct = 0;
    s_intersect i_sct;
    std::vector<s_intersect>  i_scts;
    s_rgb_triple i_clr;
    Imf::Rgba*   i_pxl;
    //bool first_surf = true;
    
    // parse the scene file
    input_scene(scene, argv[1]);
    scene.print();

    // assigning to common constants
    d_x = scene.viewport.ix/scene.viewport.px;
    d_y = scene.viewport.iy/scene.viewport.py;
    o_x = 0.5 + scene.viewport.px/2.0;
    o_y = 0.5 + scene.viewport.py/2.0;
    
    // size image to scene specs
    img_pixels.resizeErase(scene.viewport.py, scene.viewport.px);
    
    // iterate through pixels
    for(y = 0; y < scene.viewport.py; ++y)
    for(x = 0; x < scene.viewport.px; ++x)
    {
        // generate pixel reference
        i_pxl = &img_pixels[y][x];
        // generate ray
        i_ray = s_geo_ray(scene.viewport.eye,
              scene.viewport.u*d_x*(x - o_x)
            + scene.viewport.v*d_y*(o_y - y)
            - scene.viewport.w*scene.viewport.fl);
        // iterate through surfaces
        for(z = 0; z < scene.surfaces.size(); ++z)
        {
            i_sct = scene.surfaces[z]->find_intersection(i_ray);
            /*
            if(i_sct.is_true)
                i_scts.push_back(i_sct);
            */
            // break when first surface is found
            /*
            if(ii_sct.is_true)
            {
                if(first_surf == true)
                {
                    i_sct = ii_sct;
                    first_surf = false;
                }
                else if (i_sct.t > ii_sct.t)
                    i_sct = ii_sct;
            }
            */
            if(i_sct.is_true)
                break;
        }
        /*
        if(i_scts.size() == 0)
            i_clr = PIXEL_EMPTY;
        else if(i_scts.size() == 1)
            i_clr = scene.materials[i_scts[0].mat_ptr - 1].get_mat();
        else
        {
            for(z = 1; z < i_scts.size(); ++z)
            {
                if(i_scts[which_sct].t > i_scts[z].t)
                    which_sct = z;
            }
            i_clr = scene.materials[i_scts[which_sct].mat_ptr - 1].get_mat();
        }
        */
        // assign appropriate color
        
        i_clr =
            i_sct.is_true
            ? scene.materials[i_sct.mat_ptr - 1].get_mat()
            : PIXEL_EMPTY;
        
        i_pxl->r = i_clr.r;
        i_pxl->g = i_clr.g;
        i_pxl->b = i_clr.b;
        i_pxl->a = 1.0;
    }
    
    //write to file
    output_image(argv[2], img_pixels, scene.viewport.px, scene.viewport.py);
    }
    catch(const std::exception &e)
    {
        std::cerr <<"!EXCEPTION CAUGHT!" <<e.what() <<std::endl;
        return 1;
    }
    return 0;
}

//// EOF ////
