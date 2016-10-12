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
};

//// EOF ////
