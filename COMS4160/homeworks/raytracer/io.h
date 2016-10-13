/* Filename:    io.h
 * Author:      Adam Hadar, anh2130
 * Purpose:     The file input/output for a simple raytracer.
 * Edited:      2016-10-13
 */

//******************************************************************************
// SUBROUTINE_OUTPUT_IMAGE
//******************************************************************************
void io_output_image(const char* file_name, Imf::Array2D<Imf::Rgba> &image, t_scalar width, t_scalar height)
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
void io_output_scene(const s_scene& sc)
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
void io_output_scene_verbose(const s_scene& sc)
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

//******************************************************************************
// SUBROUTINE_INPUT_SCENE
//******************************************************************************
void io_input_scene(s_scene &sc, const char* file_name)
{
    // memory allocation
    // I didn't want to allocate unique blocks of memory for each case, so I reuse the
    //   same memory.
    t_uint       line;
    t_uint       ct_cameras, ct_lights, ct_materials;
    t_uint       u1, u2;
    t_scalar s1, s2, s3;
    s_geo_vector gv1;
    s_geo_point  gp1, gp2, gp3;
    s_clr_color  cc1, cc2;
   
    // there will be two asserts - there must be at least one camera, and one non-ambient light
    //   and there will be a warning if the material count doesn't increase
    ct_cameras = 0;
    ct_lights = 0;
    ct_materials = 1;

    // parse file
    std::ifstream in(file_name);
    char buffer[1025];
    std::string cmd;
    for(line = 1; in.good(); ++line)
    {
        in.getline(buffer,1024);
        buffer[in.gcount()] = 0;
        cmd = "";
        std::istringstream iss(buffer);
        iss >>cmd;
        if(cmd.empty())
            continue;
        switch (cmd[0])
        {
            // comment
            case '/':
            {
                continue;
            }
            // plane
            case 'p':
            {
                iss >>gv1 >>s1;
                sc._surfaces.push_back(new c_surf_plane(gv1,s1,ct_materials));
                break;
            }
            // triangle
            case 't':
            {
                iss >>gp1 >>gp2 >>gp3;
                sc._surfaces.push_back(new c_surf_triangle(gp1,gp2,gp3,ct_materials));
                break;
            }
            // sphere
            case 's':
            {
                iss >> gp1 >> s1;
                sc._surfaces.push_back(new c_surf_sphere(gp1,s1,ct_materials));
                break;
            }
            // light
            case 'l':
            {
                iss >> cmd;
                switch(cmd[0])
                {
                    // point
                    case 'p':
                    {
                        iss >>gp1 >>cc1;
                        sc._lights_point.push_back(new c_light_point(gp1,cc1));
                        ct_lights++;
                        break;
                    }
                    // directional
                    case 'd':
                    {
                        iss >>gv1 >>cc1;
                        gv1 = gv1*1e5;
                        sc._lights_directional.push_back(new c_light_direct(gv1,cc1));
                        ct_lights++;
                        break;
                    }
                    // ambient
                    case 'a':
                    {
                        iss >>cc1;
                        sc._light_ambient = c_light_ambient(cc1);
                        break;
                    }
                    default:
                    {
                        std::cerr <<"Parser error: invalid light command at line " <<line <<std::endl;
                    }
                }
                break;
            }
            // camera
            case 'c':
            {
                // TODO only the first camera is used
                iss >>gp1 >>gv1 >>s1 >>s2 >>s3 >>u1 >>u2;
                sc._viewports.push_back(new s_viewport(gp1,gv1,s1,s2,s3,u1,u2));
                ct_cameras++;
                break;
            }
            // material
            case 'm':
            {
                iss >>cc1 >>cc2 >>s1 >>gv1;
                // povray doesn't take reflective color, so just approximate a blend
                // weight:
                // float dlen = sqrt(refl.x*refl.x+refl.y*refl.y+refl.z*refl.z);
                sc._materials.push_back(new s_material(cc1,cc2,s1,gv1));
                ct_materials++;
                break;
            }
            default:
            {
                std::cerr <<"Parser error: invalid command at line " <<line <<std::endl;
            }
        }
    }
    in.close();
    assert(ct_cameras > 0);
    assert(ct_lights > 0);
    if(ct_materials == 1)
    {
        std::cerr <<"Warning: no materials declared" <<std::endl;
    }
    return;
}

//// EOF ////
