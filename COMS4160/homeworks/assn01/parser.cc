#include "parser.h"

/*
void POVRayParser::pointLight(float3 pos, float3 rgb) {
  cout << "light_source {" << endl;
  cout << "  " << pos << endl;
  cout << "  color rgb " << rgb << endl;
  cout << "}" << endl;
}
*/
/*
void POVRayParser::directionalLight(float3 dir, float3 rgb) {
  // povray has no directional lights, so
  // approximate with a faraway point light
  dir.x*=(100000.0);
  dir.y*=(100000.0);
  dir.z*=(100000.0);
  cout << "light_source {" << endl;
  cout << "  " << dir << endl;
  cout << "  color rgb " << rgb << endl;
  cout << "}" << endl;
}
*/
/*
void POVRayParser::ambientLight(float3 rgb) {
  ostringstream os;
  os << "global_settings { ambient_light rgb " << rgb << "}" << endl;
  aStr = os.str();
}
*/

void Parser::parse(const char *file)
{
    uint i, line;
    uint u1, u2;
    scalar s1, s2, s3;
    geo_vector gv1;
    geo_point gp1, gp2, gp3;
    rgb_triple r1, r2;
    // parse file
    std::ifstream in(file);
    char buffer[1025];
    std::string cmd;
    for(line = 1; in.good(); ++line)
    {
        in.getline(buffer,1024);
        buffer[in.gcount()]=0;
        cmd = "";
        std::istringstream iss(buffer);
        iss >> cmd;
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
                iss >> gv1 >> s1;
                surfaces.push_back(new surf_plane(gv1,s1,cur_material));
                break;
            }
            // triangle
            case 't':
            {
                iss >> gp1 >> gp2 >> gp3;
                surfaces.push_back(new surf_triangle(gp1,gp2,gp3,cur_material));
                break;
            }
            // sphere
            case 's':
            {
                iss >> gp1 >> s1;
                surfaces.push_back(new surf_sphere(gp1,s1,cur_material));
                break;
            }
            //// light
            //case 'l':
            //{
            //    iss >> cmd;
            //    switch(cmd[0])
            //    {
            //        // point
            //        case 'p':
            //        {
            //            geo_point pos; rgb_triple rgb;
            //            iss >> pos >> rgb;
            //            lights.push_back(new lit_point(pos,rgb));
            //            break;
            //        }
            //        // directional
            //        case 'd':
            //        {
            //            goe_vector dir; rgb_triple rgb;
            //            iss >> dir >> rgb;
            //            lights.push_back(new lit_direct(dir,rgb));
            //            break;
            //        }
            //        // ambient
            //        case 'a':
            //        {
            //            rgb_triple rgb;
            //            iss >> rgb;
            //            lights.push_back(new lit_ambient(rgb));
            //            break;
            //        }
            //        default:
            //        {
            //            std::cout << Parser error: invalid light command at line " << line<<std::endl;
            //        }
            //    }
            //    break;
            //}
            // camera
            case 'c':
            {
                iss >> gp1 >> gv1 >> s1 >> s2 >> s3 >> u1 >> u2;
                viewport = Viewport(gp1,gv1,s1,s2,s3,u1,u2);
                break;
            }
            // material
            case 'm':
            {
                iss >> r1 >> r2 >> s1 >> gv1;
                // povray doesn't take reflective color, so just approximate a blend
                // weight:
                // float dlen = sqrt(refl.x*refl.x+refl.y*refl.y+refl.z*refl.z);
                materials.push_back(Material(r1,r2,s1,gv1));
                cur_material++;
                break;
            }
            default:
            {
                std::cout << "Parser error: invalid command at line " << line << std::endl;
            }
        }
    }
    in.close();
    // print camera
    std::cout << "camera {" << std::endl;
    std::cout << "  location " << viewport.eye << std::endl;
    std::cout << "  focal length " << viewport.fl << std::endl;
    std::cout << "  u_vec " << viewport.u << std::endl;
    std::cout << "  v_vec " << viewport.v << std::endl;
    std::cout << "  w_vec " << viewport.w << std::endl;
    std::cout << "}" << std::endl;
    // print object list
    for(i = 0; i < surfaces.size(); ++i)
    {
        std::cout << "object "<< i+1 << " {" << std::endl;
        surfaces[i]->print();
        std::cout<< "    material " << surfaces[i]->mat_ptr << std::endl;
        std::cout << "}" << std::endl;
    }
    // print material list
    for(i = 0; i < materials.size(); ++i)
    {
        std::cout << "material " << i+1 << " {" << std::endl;
        std::cout << materials[i];
        std::cout << "}" << std::endl;
    }
    // print light list
    std::cout << "global_settings{ ambient_light rgb <0,0,>}" << std::endl;
}
