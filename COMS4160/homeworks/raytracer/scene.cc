// Filename:    scene.cc
// Author:      Adam Hadar, anh2130
// Purpose:     Definition of a scene for a simple raytracer.
// Edited:      2016-10-30

#include "common.h"
#include "geometry.h"
#include "intersection.h"
#include "surfaces.h"
#include "color.h"
#include "lights.h"
#include "materials.h"
#include "viewports.h"
#include "scene.h"

//******************************************************************************
// SCENE
//******************************************************************************
// constructor
s_scene::s_scene(void)
{
    // pushing back the void, and then the default material
    //_materials.push_back(NO_MATERIAL);
    _materials.push_back(new c_mat_blinn_phong(
        s_spd_radiance(1.0,1.0,0.0),
        s_spd_radiance(0.0,0.0,0.0),
        0.0,
        s_spd_radiance(0.0,0.0,0.0)
        )
    );
    _materials.push_back(new c_mat_blinn_phong(
        s_spd_radiance(0.0,0.0,1.0),
        s_spd_radiance(0.0,0.0,1.0),
        5.0,
        s_spd_radiance(0.0,0.0,0.0)
        )
    );
    _light_ambient = c_light_ambient(s_spd_radiance(0.0,0.0,0.0));
}

// destructor
s_scene::~s_scene(void)
{
    t_uint i;
    for(i = 0; i < _surfaces.size(); i++)
        delete _surfaces[i];
    for(i = 0; i < _materials.size(); i++)
        delete _materials[i];
    for(i = 0; i < _lights_point.size(); i++)
        delete _lights_point[i];
    for(i = 0; i < _lights_directional.size(); i++)
        delete _lights_directional[i];
}

//// EOF ////
