// Filename:    viewport.cc
// Author:      Adam Hadar, anh2130
// Purpose:     Definition of a viewport for a simple raytracer.
// Edited:      2016-10-27

#include "common.h"
#include "geometry.h"
#include "viewport.h"

//******************************************************************************
// VIEWPORT
//******************************************************************************
// constructors
s_viewport::s_viewport(void){}
s_viewport::s_viewport(
    const s_geo_point& gp,
    const s_geo_vector& gv,
    const t_scalar& s1,
    const t_uint& u1,
    const t_uint& u2,
    const t_scalar& s2,
    const t_scalar& s3
):
    _eye(gp),
    _fl(s1),
    _ix(u1),
    _iy(u2),
    _px(s2),
    _py(s3)
{
    // TODO fix u if dir too close to `up`
    _uvw[0] =
        (gv.get_x() < EPSILON && -gv.get_x() < EPSILON && gv.get_z() < EPSILON && -gv.get_z() < EPSILON)
        ? s_geo_vector(0.0,0.0,1.0)
        : gv * s_geo_vector(0.0,1.0,0.0);
    _uvw[1] = _uvw[0] * gv;
    _uvw[2] = -gv;
    _uvw[0] = _uvw[0].norm();
    _uvw[1] = _uvw[1].norm();
    _uvw[2] = _uvw[2].norm();
}

// destructor
s_viewport::~s_viewport(void){}

// get contents
s_geo_point s_viewport::get_eye(void) const
{
    return _eye;
}
s_geo_vector s_viewport::get_u(void) const
{
    return _uvw[0];
}
s_geo_vector s_viewport::get_v(void) const
{
    return _uvw[1];
}
s_geo_vector s_viewport::get_w(void) const
{
    return _uvw[2];
}
t_scalar s_viewport::get_fl(void) const
{
    return _fl;
}
t_uint s_viewport::get_ix(void) const
{
    return _ix;
}
t_uint s_viewport::get_iy(void) const
{
    return _iy;
}
t_uint s_viewport::get_px(void) const
{
    return _px;
}
t_uint s_viewport::get_py(void) const
{
    return _py;
}

//// EOF ////
