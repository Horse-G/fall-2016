/*
 * Filename:    scene.h
 * Author:      Adam Hadar, anh2130
 * Purpose:     Definition of a scene for a simple raytracer.
 * Edited:      2016-10-08
 */

//************************************************************************
// SCENE
//************************************************************************
struct s_scene
{
    s_viewport                   viewport;
    std::vector<c_surface*>      surfaces;
    std::vector<s_material>      materials;
    s_light_ambient              ambient;
    std::vector<c_light_point*>  point_lights;
    std::vector<c_light_direct*> directional_lights;

    // constructor
    s_scene(void)
    {
        materials.push_back(NO_MATERIAL);
        materials.push_back(DEFAULT_MATERIAL);
        ambient = s_light_ambient(DEFAULT_AMBIENT);
    }

    // destructor
    ~s_scene(void)
    {
        t_uint i;
        for(i = 0; i < surfaces.size(); i++)
            delete surfaces[i];
        for(i = 0; i < point_lights.size(); i++)
            delete point_lights[i];
        for(i = 0; i < directional_lights.size(); i++)
            delete directional_lights[i];
    }

    // print
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
                <<OUT_TAB <<"material " <<surfaces[i]->get_material() <<std::endl
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
        // print directional light list
        for(i = 0; i < point_lights.size(); ++i)
        {
            std::cout <<"light_source " <<i+1 <<" {" <<std::endl;
            point_lights[i]->print(OUT_TAB);
            std::cout <<"}" <<std::endl;
        }
        // print directional light list
        for(i = 0; i < directional_lights.size(); ++i)
        {
            std::cout <<"light_source " <<i+1 <<" {" <<std::endl;
            directional_lights[i]->print(OUT_TAB);
            std::cout <<"}" <<std::endl;
        }
        return;
    }
};

//// EOF ////
