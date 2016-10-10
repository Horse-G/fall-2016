/*
 * Filename:    io.h
 * Author:      Adam Hadar, anh2130
 * Purpose:     The file input/output for a simple raytracer.
 * Edited:      2016-10-09
 */

//************************************************************************
// SUBROUTINE_OUTPUT_IMAGE
//************************************************************************
void io_output_image(const char* file_name, Imf::Array2D<Imf::Rgba> &image, t_scalar width, t_scalar height)
{
    Imf::RgbaOutputFile file(file_name, width, height, Imf::WRITE_RGBA);
    file.setFrameBuffer(&image[0][0], 1, width);
    file.writePixels(height);
    return;
}

//************************************************************************
// SUBROUTINE_OUTPUT_SCENE_VERBOSE
//************************************************************************
void io_output_scene_verbose(const s_scene& sc)
{
    t_uint i;

    // camera
    std::cout
        <<"camera {" <<std::endl
        <<OUT_TAB <<"eye "   <<sc.viewport.get_eye() <<std::endl
        <<OUT_TAB <<"u "     <<sc.viewport.get_u() <<std::endl
        <<OUT_TAB <<"v "     <<sc.viewport.get_v() <<std::endl
        <<OUT_TAB <<"w "     <<sc.viewport.get_w() <<std::endl
        <<OUT_TAB <<"fl "    <<sc.viewport.get_fl() <<std::endl
        <<OUT_TAB <<"ix,iy " <<sc.viewport.get_ix() <<"," <<sc.viewport.get_iy() <<std::endl
        <<OUT_TAB <<"px,py " <<sc.viewport.get_px() <<"," <<sc.viewport.get_py() <<std::endl
        <<"}"<< std::endl;
    
    // surface list
    for (i = 0; i < sc.surfaces.size(); ++i)
    {
        std::cout
            <<"surface " <<i+1 <<" {" <<std::endl
            <<OUT_TAB <<"type " <<sc.surfaces[i]->get_type() <<std::endl
            <<OUT_TAB <<"material " <<sc.surfaces[i]->get_material() <<std::endl
            <<"}" <<std::endl;
    }
    // material list
    for(i = 0; i < sc.materials.size(); ++i)
        std::cout
            <<"material " <<i+1 << " {" <<std::endl
            <<OUT_TAB << std::endl
            <<"}" <<std::endl;
    
    // ambient light
    std::cout
        << "ambient light {" <<std::endl
        <<OUT_TAB << std::endl
        <<"}" <<std::endl;
    
    // point light list
    for(i = 0; i < sc.lights_point.size(); ++i)
        std::cout
            <<"point_light " <<i+1 <<" {" <<std::endl
            <<OUT_TAB <<std::endl
            <<"}" <<std::endl;
    
    // directional light list
    for(i = 0; i < sc.lights_directional.size(); ++i)
        std::cout
            <<"directional_light " <<i+1 << " {" <<std::endl
            <<OUT_TAB <<std::endl
            <<"}" <<std::endl;
    return;
}

//************************************************************************
// SUBROUTINE_INPUT_SCENE
//************************************************************************
void io_input_scene(s_scene &sc, const char *file_name)
{
    // memory allocation
    t_uint line;
    t_uint u1, u2;
    t_scalar s1, s2, s3;
    s_geo_vector gv1;
    s_geo_point gp1, gp2, gp3;
    s_clr_color cc1, cc2;
    
    bool ct_camera = false;

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
                sc.surfaces.push_back(new c_surf_plane(gv1,s1,sc.materials.size()));
                break;
            }
            // triangle
            case 't':
            {
                iss >>gp1 >>gp2 >>gp3;
                sc.surfaces.push_back(new c_surf_triangle(gp1,gp2,gp3,sc.materials.size()));
                break;
            }
            // sphere
            case 's':
            {
                iss >> gp1 >> s1;
                sc.surfaces.push_back(new c_surf_sphere(gp1,s1,sc.materials.size()));
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
                        sc.lights_point.push_back(new c_light_point(gp1,cc1));
                        break;
                    }
                    // directional
                    case 'd':
                    {
                        iss >>gv1 >>cc1;
                        gv1 = gv1*1e5;
                        sc.lights_directional.push_back(new c_light_direct(gv1,cc1));
                        break;
                    }
                    // ambient
                    case 'a':
                    {
                        iss >>cc1;
                        sc.light_ambient = c_light_ambient(cc1);
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
                iss >>gp1 >>gv1 >>s1 >>s2 >>s3 >>u1 >>u2;
                sc.viewport = s_viewport(gp1,gv1,s1,s2,s3,u1,u2);
                ct_camera = true;
                break;
            }
            // material
            case 'm':
            {
                iss >>cc1 >>cc2 >>s1 >>gv1;
                // povray doesn't take reflective color, so just approximate a blend
                // weight:
                // float dlen = sqrt(refl.x*refl.x+refl.y*refl.y+refl.z*refl.z);
                sc.materials.push_back(s_material(cc1,cc2,s1,gv1));
                break;
            }
            default:
            {
                std::cerr <<"Parser error: invalid command at line " <<line <<std::endl;
            }
        }
    }
    in.close();
    assert(ct_camera == true);
    return;
}

//// EOF ////
