// Filename:    data_output.h
// Author:      Adam Hadar, anh2130
// Purpose:     The data output for a simple raytracer.
// Edited:      2016-10-30

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

//******************************************************************************
// SUBROUTINE_OUTPUT_SCENE
//******************************************************************************
void output_scene(const s_scene& sc, const s_rig_vps& rig)
{
    std::cout
        <<"Camera Count:             " <<rig._count                    <<std::endl
        <<"Surfaces Count:           " <<sc._surfaces.size()           <<std::endl
        <<"Materials Count:          " <<sc._materials.size()          <<std::endl
        <<"Point Lights Count:       " <<sc._lights_point.size()       <<std::endl
        <<"Directional Lights Count: " <<sc._lights_directional.size() <<std::endl;
    return;
}

//******************************************************************************
// SUBROUTINE_OUTPUT_SCENE_VERBOSE
//******************************************************************************
void output_scene_verbose(const s_scene& sc, const s_rig_vps& rig)
{
    // memory allocation
    t_uint i;

    // camera list
    for (i = 0; i < rig._count; ++i)
    {
        std::cout
            <<"camera {" <<std::endl
            <<"    " <<"eye "   <<rig._list[i]->get_eye() <<std::endl
            <<"    " <<"u "     <<rig._list[i]->get_u()   <<std::endl
            <<"    " <<"v "     <<rig._list[i]->get_v()   <<std::endl
            <<"    " <<"w "     <<rig._list[i]->get_w()   <<std::endl
            <<"    " <<"fl "    <<rig._list[i]->get_fl()  <<std::endl
            <<"    " <<"ix,iy " <<rig._list[i]->get_ix() <<"," <<rig._list[i]->get_iy() <<std::endl
            <<"    " <<"px,py " <<rig._list[i]->get_px() <<"," <<rig._list[i]->get_py() <<std::endl
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
                    <<"    " <<"type     " <<"plane"             <<std::endl
                    <<"    " <<"normal   " <<tmp->get_normal()   <<std::endl
                    <<"    " <<"distance " <<tmp->get_distance() <<std::endl;
            }
            case TRIANGLE:
            {
                c_surf_triangle* tmp = static_cast<c_surf_triangle*>(sc._surfaces[i]);
                std::cout
                    <<"    " <<"type     " <<"triangle"        <<std::endl
                    <<"    " <<"v1       " <<tmp->get_v1()     <<std::endl
                    <<"    " <<"v2       " <<tmp->get_v2()     <<std::endl
                    <<"    " <<"v3       " <<tmp->get_v3()     <<std::endl
                    <<"    " <<"normal   " <<tmp->get_normal() <<std::endl;
            }
            case SPHERE:
            {
                c_surf_sphere* tmp = static_cast<c_surf_sphere*>(sc._surfaces[i]);
                std::cout
                    <<"    " <<"type     " <<"sphere"          <<std::endl
                    <<"    " <<"origin   " <<tmp->get_origin() <<std::endl
                    <<"    " <<"radius   " <<tmp->get_radius() <<std::endl;
            }
            default:
            {
                std::cout
                    <<"    " <<"illegal surface" <<std::endl;
                break;
            }
        }
        std::cout <<"}" <<std::endl;
    }
    // material list
    for(i = 0; i < sc._materials.size(); ++i)
        std::cout
            <<"material " <<i+1 << " {" <<std::endl
            <<"    " <<"diffuse    " <<sc._materials[i]->get_diff() <<std::endl
            <<"    " <<"specular   " <<sc._materials[i]->get_spec() <<std::endl
            <<"    " <<"reflection " <<sc._materials[i]->get_refl() <<std::endl
            <<"    " <<"phong      " <<sc._materials[i]->get_phng() <<std::endl
            <<"}" <<std::endl;
    // ambient light
    std::cout
        <<"light 1 ambient {" <<std::endl
        <<"    " <<"color " <<sc._light_ambient.get_radiance() <<std::endl
        <<"}" <<std::endl;
    // point light list
    for(i = 0; i < sc._lights_point.size(); ++i)
        std::cout
            <<"light " <<i+2 <<" point {" <<std::endl
            <<"    " << "point " <<sc._lights_point[i]->get_point()    <<std::endl
            <<"    " << "color " <<sc._lights_point[i]->get_radiance() <<std::endl
            <<"}" <<std::endl;
    
    // directional light list
    for(i = 0; i < sc._lights_directional.size(); ++i)
        std::cout
            <<"light " <<i+2+sc._lights_point.size() << " directional {" <<std::endl
            <<"    " << "vector " <<sc._lights_directional[i]->get_direction() <<std::endl
            <<"    " << "color  " <<sc._lights_directional[i]->get_radiance()  <<std::endl
            <<"}" <<std::endl;
    return;
}

//// EOF ////
