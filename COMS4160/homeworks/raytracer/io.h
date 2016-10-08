/*
 * Filename:    io.h
 * Author:      Adam Hadar, anh2130
 * Purpose:     The file input/output for a simple raytracer.
 * Edited:      2016-10-08
 */

//************************************************************************
// SUBROUTINE_OUTPUT_IMAGE
//************************************************************************
void output_image(const char* file_name, Imf::Array2D<Imf::Rgba> &image, t_scalar width, t_scalar height)
{
    Imf::RgbaOutputFile file(file_name, width, height, Imf::WRITE_RGBA);
    file.setFrameBuffer(&image[0][0], 1, width);
    file.writePixels(height);
    return;
}

//************************************************************************
// SUBROUTINE_INPUT_SCENE
//************************************************************************
void input_scene(s_scene &sc, const char *file_name)
{
    // memory allocation
    t_uint line;
    t_uint u1, u2;
    t_scalar s1, s2, s3;
    s_geo_vector gv1;
    s_geo_point gp1, gp2, gp3;
    s_rgb_triple r1, r2;
        
    // parse file
    std::ifstream in(file_name);
    char buffer[1025];
    std::string cmd;
    for(line = 1; in.good(); ++line)
    {
        in.getline(buffer,1024);
        buffer[in.gcount()]=0;
        cmd = "";
        std::istringstream iss(buffer);
        iss >>cmd;
        if(cmd.empty())
            continue;
        switch (cmd[0])
        {
            // comment
            case '/':{
                continue;}
            // plane
            case 'p':{
                iss >>gv1 >>s1;
                sc.surfaces.push_back(new c_surf_plane(gv1,s1,sc.materials.size()));
                break;}
            // triangle
            case 't':{
                iss >>gp1 >>gp2 >>gp3;
                sc.surfaces.push_back(new c_surf_triangle(gp1,gp2,gp3,sc.materials.size()));
                break;}
            // sphere
            case 's':{
                iss >> gp1 >> s1;
                sc.surfaces.push_back(new c_surf_sphere(gp1,s1,sc.materials.size()));
                break;}
            // light
            case 'l':{
                iss >> cmd;
                switch(cmd[0])
                {
                    // point
                    case 'p':{
                        iss >>gp1 >>r1;
                        sc.point_lights.push_back(new c_light_point(gp1,r1));
                        break;}
                    // directional
                    case 'd':{
                        iss >>gv1 >>r1;
                        gv1 = gv1*1e5;
                        sc.directional_lights.push_back(new c_light_direct(gv1,r1));
                        break;}
                    // ambient
                    case 'a':{
                        iss >>r1;
                        sc.ambient = s_light_ambient(r1);
                        break;}
                    default:{
                        std::cerr <<"Parser error: invalid light command at line " <<line <<std::endl;}
                }
                break;}
            // camera
            case 'c':{
                iss >>gp1 >>gv1 >>s1 >>s2 >>s3 >>u1 >>u2;
                sc.viewport = s_viewport(gp1,gv1,s1,s2,s3,u1,u2);
                break;}
            // material
            case 'm':{
                iss >>r1 >>r2 >>s1 >>gv1;
                // povray doesn't take reflective color, so just approximate a blend
                // weight:
                // float dlen = sqrt(refl.x*refl.x+refl.y*refl.y+refl.z*refl.z);
                sc.materials.push_back(s_material(r1,r2,s1,gv1));
                break;}
            default:{
                std::cerr <<"Parser error: invalid command at line " <<line <<std::endl;}
        }
    }
    in.close();
    return;
}

//// EOF ////
