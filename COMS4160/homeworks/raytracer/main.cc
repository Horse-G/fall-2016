// Filename:    main.cc
// Author:      Adam Hadar, anh2130
// Purpose:     The main function for a simple raytracer.
// Edited:      2016-10-30

#include "common.h"
#include "geometry.h"
#include "intersection.h"
#include "surfaces.h"
#include "color.h"
#include "lights.h"
#include "materials.h"
#include "viewport.h"
#include "scene.h"
#include "data_input.h"
#include "data_output.h"
#include "raytrace.h"

//******************************************************************************
// ROUTINE_MAIN
//******************************************************************************
int main(int argc, char** argv)
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
        Imf::Array2D<Imf::Rgba>  img_pixels;
        s_scene                  scene;
        std::vector<s_viewport*> viewports;
        t_scalar                 v_px, v_py;

        t_uint i;
        v_px = 0.0;
        v_py = 0.0;

        // parse the scene file
        input_scene(scene, viewports, argv[1]);
        //print_scene_verbose();
    
        // generate image dimensions
        //    makes a very wide image
        for(i = 0; i < viewports.size(); ++i)
        {
            t_scalar i_px = viewports[i]->get_px();
            t_scalar i_py = viewports[i]->get_py();
            
            v_px += i_px;
            if(i_py > v_py)
                v_py = i_py;
        }
        img_pixels.resizeErase(v_py, v_px);

        // do the raytrace for each viewport
        t_scalar px_start = 0.0;
        t_scalar py_start = 0.0;
        for(i = 0; i < viewports.size(); ++i)
        {
            t_scalar px_end = viewports[i]->get_px();
            t_scalar py_end = viewports[i]->get_py();
            raytrace_do(img_pixels, px_start, px_start + px_end, py_start, py_start + py_end, scene, *viewports[i]);
            px_start += px_end;
            // py_start += 
        }
        
        //write to file
        output_image(argv[2], img_pixels, v_px, v_py);

        for(i = 0; i < viewports.size(); ++i)
        {
            delete viewports[i];
        }
    }
    catch(const std::exception& e)
    {
        std::cerr <<"!EXCEPTION CAUGHT!" <<e.what() <<std::endl;
        return 1;
    }
    return 0;
}

//// EOF ////
