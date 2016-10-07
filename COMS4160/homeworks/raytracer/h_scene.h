/*
 * Filename:    h_scene.h
 * Author:      Adam Hadar, anh2130
 * Purpose:     Definition of a scene object for a simple raytracer.
 * Edited:      2016-10-06
 */

//************************************************************************
// VIEWPORT
//************************************************************************
struct s_viewport
{
    s_geo_point eye;
    t_scalar fl;
    s_geo_vector u, v, w;
    t_uint ix, iy;
    t_scalar px, py;

    s_viewport(){}
    s_viewport(s_geo_point _eye, s_geo_vector dir, t_scalar _fl, t_uint _ix, t_uint _iy, t_scalar _px, t_scalar _py):
        eye(_eye),
        fl(_fl),
        ix(_ix),
        iy(_iy),
        px(_px),
        py(_py)
    {
        u = dir * s_geo_vector(0.0,1.0,0.0);
        v = u * dir;
        w = -dir;
        u = u.norm();
        v = v.norm();
        w = w.norm();
    }
    void print(const char* tab)
    {
        std::cout
            <<tab <<"eye "   <<eye         <<std::endl
            <<tab <<"u "     <<u           <<std::endl
            <<tab <<"v "     <<v           <<std::endl
            <<tab <<"w "     <<w           <<std::endl
            <<tab <<"fl "    <<fl          <<std::endl
            <<tab <<"ix,iy " <<ix<<","<<iy <<std::endl
            <<tab <<"px,py " <<px<<","<<iy <<std::endl;
        return;
    }
};

//************************************************************************
// SCENE
//************************************************************************
struct s_scene
{
    s_viewport viewport;
    std::vector<c_surface*> surfaces;
    std::vector<s_material> materials;
    s_light_ambient ambient;
    std::vector<c_light*> lights;

    // constructor
    s_scene()
    {
        materials.push_back(DEFAULT_MATERIAL);
        ambient = s_light_ambient(DEFAULT_AMBIENT);
    }
    // destructor
    ~s_scene()
    {
        t_uint i;
        for(i = 0; i < surfaces.size(); i++)
            delete surfaces[i];
        for(i = 0; i < lights.size(); i++)
            delete lights[i];
    }
    // printing the entire scene
    void print(void)
    {
        t_uint i;
        std::cout <<"camera {" <<std::endl;
        viewport.print(OUT_TAB);
        std::cout <<"}"        <<std::endl;
        // print object list
        for(i = 0; i < surfaces.size(); ++i)
        {
            std::cout <<"object " <<i+1 <<" {"                 <<std::endl;
            surfaces[i]->print(OUT_TAB);
            std::cout
                <<OUT_TAB <<"material " <<surfaces[i]->get_mat() <<std::endl
                << "}"                                         <<std::endl;
        }
        // print material list
        for(i = 0; i < materials.size(); ++i)
        {
            std::cout <<"material " <<i+1 <<" {" <<std::endl;
            materials[i].print(OUT_TAB);
            std::cout <<"}"                      <<std::endl;
        }
        // print ambient light
        std::cout <<"global_settings {"<<std::endl;
        ambient.print(OUT_TAB);
        std::cout <<"}"                <<std::endl;
        // print light list
        for(i = 0; i < lights.size(); ++i)
        {
            std::cout <<"light_source " <<i+1 <<" {" <<std::endl;
            lights[i]->print(OUT_TAB);
            std::cout <<"}" <<std::endl;
        }
        return;
    }
};

//// EOF ////
