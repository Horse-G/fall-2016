// Filename:    intersection.cc
// Author:      Adam Hadar, anh2130
// Purpose:     Definitions for intersections for a simple raytracer.
// Edited:      2016-10-27

#include "common.h"
#include "geometry.h"
#include "intersection.h"

//******************************************************************************
// STRUCT_INTERSECTION
//******************************************************************************
    // constructors
s_intersect::s_intersect(void): _is_true(false) {}
s_intersect::s_intersect(const t_scalar& s, const s_geo_point& gp, const s_geo_vector& gv, const t_uint& u, const t_surface& ts):
    _is_true(true),
    _t(s),
    _point(gp),
    _normal(gv),
    _material(u),
    _surf_type(ts) {}
s_intersect::s_intersect(const t_scalar& s): _is_true(false), _t(s) {}

    // destructor
s_intersect::~s_intersect(void){}

    // get contents
bool s_intersect::get_is_true(void) const
{
    return _is_true;
}
t_scalar s_intersect::get_t(void) const
{
    return _t;
}
s_geo_point s_intersect::get_point(void) const
{
    return _point;
}
s_geo_vector s_intersect::get_normal(void) const
{
    return _normal;
}
t_uint s_intersect::get_material(void) const
{
    return _material;
}
t_surface s_intersect::get_surf_type(void) const
{
    return _surf_type;
}

//// EOF ////
