// Filename:    data_input.h
// Author:      Adam Hadar, anh2130
// Purpose:     The data input for a simple raytracer.
// Edited:      2016-10-30

//******************************************************************************
// SUBROUTINE_INPUT_OBJ
//******************************************************************************
void input_obj(const std::string file_name, std::vector<t_uint>& tris, std::vector<s_geo_point>& verts)
{
    t_uint line;
    tris.clear();
    verts.clear();
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
        switch(cmd[0])
        {
            case '#':
            {
                continue;
            }
            case 'v':
            {
                t_scalar pa, pb, pc;
                iss >>pa >>pb >>pc;
                verts.push_back(s_geo_point(pa,pb,pc));
                break;
            }
            case 'f':
            {
                int i, j, k;
                iss >>i >>j >>k;
                tris.push_back(i-1);
                tris.push_back(j-1);
                tris.push_back(k-1);
                break;
            }
            default:
            {
                std::cout <<"Parser error: invalid command at line " <<line <<"in file " << file_name<<std::endl;
            }
        }
    }
    in.close();
}

//******************************************************************************
// SUBROUTINE_INPUT_SCENE
//******************************************************************************
void input_scene(s_scene &sc, s_rig_vps& rig, const char* file_name)
{
    // memory allocation
    // I didn't want to allocate unique blocks of memory for each case, so I reuse the
    //   same memory.
    t_uint         line;
    t_uint         ct_cameras, ct_lights, ct_materials;
    t_uint         u1, u2;
    t_scalar       s1, s2, s3;
    s_geo_vector   gv1;
    s_geo_point    gp1, gp2, gp3;
    s_spd_radiance spdr1, spdr2, spdr3;
   
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
            // obj file
            case 'w':
            {
                std::vector<t_uint> triangles;
                std::vector<s_geo_point> vertices;
                std::string file_name;
                file_name = "";
                iss >>file_name;
                input_obj(file_name, triangles, vertices);
                for(t_uint i = 0; i < triangles.size(); i = i + 3)
                {
                    gp1 = vertices[triangles[i]];
                    gp2 = vertices[triangles[i + 1]];
                    gp3 = vertices[triangles[i + 2]];
                    sc._surfaces.push_back(new c_surf_triangle(gp1,gp2,gp3,ct_materials));
                }
                break;
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
                        iss >>gp1 >>spdr1;
                        sc._lights_point.push_back(new c_light_point(gp1,spdr1));
                        ct_lights++;
                        break;
                    }
                    // directional
                    case 'd':
                    {
                        iss >>gv1 >>spdr1;
                        gv1 = gv1*1e5;
                        sc._lights_directional.push_back(new c_light_direct(gv1,spdr1));
                        ct_lights++;
                        break;
                    }
                    // ambient
                    case 'a':
                    {
                        iss >>spdr1;
                        sc._light_ambient = c_light_ambient(spdr1);
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
                rig._list.push_back(new c_vp_default(gp1,gv1,s1,s2,s3,u1,u2));
                ct_cameras++;
                break;
            }
            // material
            case 'm':
            {
                iss >>spdr1 >>spdr2 >>s1 >>spdr3;
                // povray doesn't take reflective color, so just approximate a blend
                // weight:
                // float dlen = sqrt(refl.x*refl.x+refl.y*refl.y+refl.z*refl.z);
                sc._materials.push_back(new c_mat_blinn_phong(spdr1,spdr2,s1,spdr3));
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
    rig._count = ct_cameras;
    assert(ct_lights > 0);
    if(ct_materials <= 1)
    {
        std::cerr <<"Warning: no materials declared" <<std::endl;
    }
    return;
}

//// EOF ////
