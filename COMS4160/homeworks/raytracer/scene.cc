// Filename:    scene.cc
// Author:      Adam Hadar, anh2130
// Purpose:     Definition of a scene for a simple raytracer.
// Edited:      2016-10-27

#include "common.h"
#include "geometry.h"
#include "intersection.h"
#include "surfaces.h"
#include "color.h"
#include "lights.h"
#include "materials.h"
#include "viewport.h"
#include "scene.h"

//******************************************************************************
// SCENE
//******************************************************************************
// constructor
s_scene::s_scene(void)
{
    // pushing back the void, and then the default material
    //_materials.push_back(NO_MATERIAL);
    _materials.push_back(DEFAULT_MATERIAL);
    _light_ambient = DEFAULT_AMBIENT;
}

// destructor
s_scene::~s_scene(void)
{
    t_uint i;
    for(i = 0; i < _viewports.size(); i++)
        delete _viewports[i];
    for(i = 0; i < _surfaces.size(); i++)
        delete _surfaces[i];
    for(i = 0; i < _materials.size(); i++)
        delete _materials[i];
    for(i = 0; i < _lights_point.size(); i++)
        delete _lights_point[i];
    for(i = 0; i < _lights_directional.size(); i++)
        delete _lights_directional[i];
}

// get contents
//   These are the only necessary, because the other accessing functions
//     have friend access;
t_scalar s_scene::get_vpx(void) const
{
    return _viewports[0]->get_px();
}
t_scalar s_scene::get_vpy(void) const
{
    return _viewports[0]->get_py();
}

//// EOF ////
