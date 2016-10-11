/*
 * Filename:    scene.h
 * Author:      Adam Hadar, anh2130
 * Purpose:     Definition of a scene for a simple raytracer.
 * Edited:      2016-10-11
 */

//************************************************************************
// SCENE
//************************************************************************
struct s_scene
{
    std::vector<s_viewport*>     viewports;
    std::vector<c_surface*>      surfaces;
    std::vector<s_material>      materials;
    c_light_ambient              light_ambient;
    std::vector<c_light_point*>  lights_point;
    std::vector<c_light_direct*> lights_directional;

    // constructor
    s_scene(void)
    {
        materials.push_back(NO_MATERIAL);
        materials.push_back(DEFAULT_MATERIAL);
        light_ambient = DEFAULT_AMBIENT;
    }

    // destructor
    ~s_scene(void)
    {
        t_uint i;
        for(i =0; i < viewports.size(); i++)
            delete viewports[i];
        for(i = 0; i < surfaces.size(); i++)
            delete surfaces[i];
        for(i = 0; i < lights_point.size(); i++)
            delete lights_point[i];
        for(i = 0; i < lights_directional.size(); i++)
            delete lights_directional[i];
    }

    // print
    void print(void)
    {
        std::cout
            <<"Camera Count: "             <<viewports.size()          <<std::endl
            <<"Surfaces Count: "           <<surfaces.size()           <<std::endl
            <<"Materials Count: "          <<materials.size()          <<std::endl
            <<"Point Lights Count: "       <<lights_point.size()       <<std::endl
            <<"Directional Lights Count: " <<lights_directional.size() <<std::endl;
        return;
    }
    // print verbose
    void print_verbose(void)
    {
        t_uint i;
        // print camera list
        for(i = 0; i < viewports.size(); ++i)
        {
            std::cout <<"camera " <<i+1 <<" {" <<std::endl;
            viewports[i]->print(OUT_TAB);
            std::cout <<"}" <<std::endl;
        }
        // print object list
        for(i = 0; i < surfaces.size(); ++i)
        {
            std::cout <<"object " <<i+1 <<" {"                 <<std::endl;
            surfaces[i]->print(OUT_TAB);
            std::cout
                <<OUT_TAB <<"material " <<surfaces[i]->get_material() <<std::endl
                << "}"                                         <<std::endl;
        }
        // print material list
        // print ambient light
        std::cout <<"global_settings {"<<std::endl;
        light_ambient.print(OUT_TAB);
        std::cout <<"}"                <<std::endl;
        // print directional light list
        // print directional light list
        return;
    }
};

//// EOF ////
