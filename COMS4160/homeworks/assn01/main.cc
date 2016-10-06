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
    // try necessary for OpenEXR API
    try{
    // memory allocation
    Imf::Array2D<Imf::Rgba> img_pixels;
    s_scene scene;
    t_uint x,y,z;
    t_scalar d_x, d_y, o_x, o_y;
    s_geo_ray    i_ray;
    s_intersect  i_sct;
    s_rgb_triple i_clr;
    Imf::Rgba*   i_pxl;
    
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
            // break when first surface is found
            if(i_sct.is_true)
                break;
        }
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
    output_image(FILE_OUT, img_pixels, scene.viewport.px, scene.viewport.py);
    
    // closing the routine
    }
    catch(const std::exception &e)
    {
        std::cerr <<"!EXCEPTION CAUGHT!" <<e.what() <<std::endl;
        return 1;
    }
    return 0;
}

//// EOF ////
