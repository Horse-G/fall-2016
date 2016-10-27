// Filename:    data_output.h
// Author:      Adam Hadar, anh2130
// Purpose:     The data output for a simple raytracer.
// Edited:      2016-10-27

//******************************************************************************
// SUBROUTINE_OUTPUT_IMAGE
//******************************************************************************
void output_image(const char* file_name, Imf::Array2D<Imf::Rgba> &image, const t_scalar& width, const t_scalar& height)
{
    Imf::RgbaOutputFile file(file_name, width, height, Imf::WRITE_RGBA);
    file.setFrameBuffer(&image[0][0], 1, width);
    file.writePixels(height);
    return;
}

#ifdef PRINT
//******************************************************************************
// SUBROUTINE_OUTPUT_SCENE
//******************************************************************************
void output_scene(const s_scene& sc)
{
    std::cout
        <<"Camera Count:             " <<sc._viewports.size()          <<std::endl
        <<"Surfaces Count:           " <<sc._surfaces.size()           <<std::endl
        <<"Materials Count:          " <<sc._materials.size()          <<std::endl
        <<"Point Lights Count:       " <<sc._lights_point.size()       <<std::endl
        <<"Directional Lights Count: " <<sc._lights_directional.size() <<std::endl;
    return;
}

//******************************************************************************
// SUBROUTINE_OUTPUT_SCENE_VERBOSE
//******************************************************************************
void output_scene_verbose(const s_scene& sc)
{
    // memory allocation
    t_uint i;

    // camera list
    for (i = 0; i < sc._viewports.size(); ++i)
    {
        std::cout
            <<"camera {" <<std::endl
            <<OUT_TAB <<"eye "   <<sc._viewports[i]->get_eye() <<std::endl
            <<OUT_TAB <<"u "     <<sc._viewports[i]->get_u() <<std::endl
            <<OUT_TAB <<"v "     <<sc._viewports[i]->get_v() <<std::endl
            <<OUT_TAB <<"w "     <<sc._viewports[i]->get_w() <<std::endl
            <<OUT_TAB <<"fl "    <<sc._viewports[i]->get_fl() <<std::endl
            <<OUT_TAB <<"ix,iy " <<sc._viewports[i]->get_ix() <<"," <<sc._viewports[i]->get_iy() <<std::endl
            <<OUT_TAB <<"px,py " <<sc._viewports[i]->get_px() <<"," <<sc._viewports[i]->get_py() <<std::endl
            <<"}"<< std::endl;
    }
    // surface list
    for (i = 0; i < sc._surfaces.size(); ++i)
    {
        std::cout
            <<"surface " <<i+1 <<" {" <<std::endl;
        switch(sc._surfaces[i]->get_type())
        {
            case PLANE:
            {
                c_surf_plane* tmp = static_cast<c_surf_plane*>(sc._surfaces[i]);
                std::cout
                    <<OUT_TAB <<"type     " <<"plane"             <<std::endl
                    <<OUT_TAB <<"normal   " <<tmp->get_normal()   <<std::endl
                    <<OUT_TAB <<"distance " <<tmp->get_distance() <<std::endl;
            }
            case TRIANGLE:
            {
                c_surf_triangle* tmp = static_cast<c_surf_triangle*>(sc._surfaces[i]);
                std::cout
                    <<OUT_TAB <<"type     " <<"triangle"        <<std::endl
                    <<OUT_TAB <<"v1       " <<tmp->get_v1()     <<std::endl
                    <<OUT_TAB <<"v2       " <<tmp->get_v2()     <<std::endl
                    <<OUT_TAB <<"v3       " <<tmp->get_v3()     <<std::endl
                    <<OUT_TAB <<"normal   " <<tmp->get_normal() <<std::endl;
            }
            case SPHERE:
            {
                c_surf_sphere* tmp = static_cast<c_surf_sphere*>(sc._surfaces[i]);
                std::cout
                    <<OUT_TAB <<"type     " <<"sphere"          <<std::endl
                    <<OUT_TAB <<"origin   " <<tmp->get_origin() <<std::endl
                    <<OUT_TAB <<"radius   " <<tmp->get_radius() <<std::endl;
            }
            default:
            {
                std::cout
                    <<OUT_TAB <<"illegal surface" <<std::endl;
                break;
            }
        }
        std::cout <<"}" <<std::endl;
    }
    // material list
    for(i = 0; i < sc._materials.size(); ++i)
        std::cout
            <<"material " <<i+1 << " {" <<std::endl
            <<OUT_TAB <<"diffuse    " <<sc._materials[i]->get_diff() <<std::endl
            <<OUT_TAB <<"specular   " <<sc._materials[i]->get_spec() <<std::endl
            <<OUT_TAB <<"reflection " <<sc._materials[i]->get_refl() <<std::endl
            <<OUT_TAB <<"phong      " <<sc._materials[i]->get_phng() <<std::endl
            <<"}" <<std::endl;
    // ambient light
    std::cout
        <<"light 1 ambient {" <<std::endl
        <<OUT_TAB <<"color " <<sc._light_ambient.get_color() <<std::endl
        <<"}" <<std::endl;
    // point light list
    for(i = 0; i < sc._lights_point.size(); ++i)
        std::cout
            <<"light " <<i+2 <<" point {" <<std::endl
            <<OUT_TAB << "point " <<sc._lights_point[i]->get_point() <<std::endl
            <<OUT_TAB << "color " <<sc._lights_point[i]->get_color() <<std::endl
            <<"}" <<std::endl;
    
    // directional light list
    for(i = 0; i < sc._lights_directional.size(); ++i)
        std::cout
            <<"light " <<i+2+sc._lights_point.size() << " directional {" <<std::endl
            <<OUT_TAB << "vector " <<sc._lights_directional[i]->get_direction() <<std::endl
            <<OUT_TAB << "color  " <<sc._lights_directional[i]->get_color() <<std::endl
            <<"}" <<std::endl;
    return;
}
#endif

//// EOF ////
