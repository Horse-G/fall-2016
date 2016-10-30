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
#include "viewports.h"
#include "scene.h"
#include "rigging.h"
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
        s_rig_vps                rig;
        t_scalar                 v_px, v_py;

        t_uint i;
        v_px = 0.0;
        v_py = 0.0;

        // parse the scene file
        input_scene(scene, rig, argv[1]);
        //print_scene_verbose();
    
        // generate image dimensions
        rig.set_dimensions(v_px, v_py);
        img_pixels.resizeErase(v_py, v_px);

        // do the raytrace for each viewport
        t_scalar px_start = 0.0;
        t_scalar py_start = 0.0;
        for(i = 0; i < rig.get_count(); ++i)
        {
            c_viewport* i_vp = rig.get_vp(i);
            t_scalar px_end = i_vp->get_px();
            t_scalar py_end = i_vp->get_py();
            raytrace_do(img_pixels, px_start, px_start + px_end, py_start, py_start + py_end, scene, *i_vp);
            px_start += px_end;
            // py_start += 
        }
        
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
