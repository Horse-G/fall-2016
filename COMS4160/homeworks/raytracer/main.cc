// Filename:    main.cc
// Author:      Adam Hadar, anh2130
// Purpose:     The main function for a simple raytracer.
// Edited:      2016-10-27

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
        Imf::Array2D<Imf::Rgba> img_pixels;
        s_scene                 scene;
        t_scalar                v_px, v_py;
    
        // parse the scene file
        input_scene(scene, argv[1]);
        #ifdef PRINT
        print_scene_verbose();
        #endif
    
        // size image to scene specs
        // had to do the resize here, because try/catch was giving an error
        v_px = scene.get_vpx();
        v_py = scene.get_vpy();
        img_pixels.resizeErase(v_py, v_px);
        // do the raytrace
        raytrace_do(img_pixels, v_px, v_py, scene);
        //write to file
        output_image(argv[2], img_pixels, v_px, v_py);
    }
    catch(const std::exception& e)
    {
        std::cerr <<"!EXCEPTION CAUGHT!" <<e.what() <<std::endl;
        return 1;
    }
    return 0;
}

//// EOF ////
