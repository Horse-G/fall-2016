// Filename:    lights.cc
// Author:      Adam Hadar, anh2130
// Purpose:     Definitions for lights for a simple raytracer.
// Edited:      2016-10-27

#include "common.h"
#include "geometry.h"
#include "color.h"
#include "lights.h"

//******************************************************************************
// VIRTUAL_CLASS_LIGHT
//******************************************************************************
// subclass destructor
c_light::~c_light(void) {}
    
// get contents
s_spd_radiance c_light::get_radiance(void) const
{
    return _radiance;
}
t_light c_light::get_type(void) const
{
    return _type;
} 

//******************************************************************************
// STRUCT_LIGHT_AMBIENT
//******************************************************************************
// constructors
c_light_ambient::c_light_ambient(void)
{
    _type = AMBIENT;
}
c_light_ambient::c_light_ambient(const s_spd_radiance& spdr)
{
    _radiance = spdr;
    _type = AMBIENT;
}

// destructor
c_light_ambient::~c_light_ambient(void){}

//******************************************************************************
// CLASS_LIGHT_POINT
//******************************************************************************
// constructors
c_light_point::c_light_point(void)
{
    _type = POINT;
}
c_light_point::c_light_point(const s_geo_point& gp, const s_spd_radiance& spdr):
    _point(gp)
{
    _radiance = spdr;
    _type = POINT;
}
c_light_point::c_light_point(const s_geo_point& gp, const s_spd_radiance& spdr, const t_scalar& s):
    _point(gp),
    _intensity(s)
{
    _radiance = spdr;
    _type = POINT;
}

// destructor
c_light_point::~c_light_point(void){}
    
// get contents
s_geo_point c_light_point::get_point(void) const
{
    return _point;
}

//******************************************************************************
// CLASS_LIGHT_DIRECTIONAL
//******************************************************************************
// constructors
c_light_direct::c_light_direct(void)
{
    _type = DIRECTIONAL;
}
c_light_direct::c_light_direct(const s_geo_vector& gv, const s_spd_radiance& spdr):
    _direction(gv)
{
    _radiance = spdr;
    _type = DIRECTIONAL;
}
    
// destructor
c_light_direct::~c_light_direct(void){}
    
// get contents
s_geo_vector c_light_direct::get_direction(void) const
{
    return _direction;
}

//// EOF ////
