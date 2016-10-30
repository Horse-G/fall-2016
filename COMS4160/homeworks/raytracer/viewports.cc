// Filename:    viewports.cc
// Author:      Adam Hadar, anh2130
// Purpose:     Definition of a viewport for a simple raytracer.
// Edited:      2016-10-30

#include "common.h"
#include "geometry.h"
#include "color.h"
#include "viewports.h"

//******************************************************************************
// VIEWPORT
//******************************************************************************
// destructor
c_viewport::~c_viewport(void){}

// get contents
s_geo_point c_viewport::get_eye(void) const
{
    return _eye;
}
s_geo_vector c_viewport::get_u(void) const
{
    return _uvw[0];
}
s_geo_vector c_viewport::get_v(void) const
{
    return _uvw[1];
}
s_geo_vector c_viewport::get_w(void) const
{
    return _uvw[2];
}
t_scalar c_viewport::get_fl(void) const
{
    return _fl;
}
t_uint c_viewport::get_ix(void) const
{
    return _ix;
}
t_uint c_viewport::get_iy(void) const
{
    return _iy;
}
t_uint c_viewport::get_px(void) const
{
    return _px;
}
t_uint c_viewport::get_py(void) const
{
    return _py;
}

//******************************************************************************
// VIEWPORT_DEFAULT
//******************************************************************************
// constructors
c_vp_default::c_vp_default(void){}
c_vp_default::c_vp_default(
    const s_geo_point& gp,
    const s_geo_vector& gv,
    const t_scalar& s1,
    const t_uint& u1,
    const t_uint& u2,
    const t_scalar& s2,
    const t_scalar& s3
)
{
    _eye = gp;
    _fl = s1;
    _ix = u1;
    _iy = u2;
    _px = s2;
    _py = s3;
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
c_vp_default::~c_vp_default(void){}

s_spd_radiance c_vp_default::filter(const s_spd_radiance& spdr) const
{
    /*
    t_scalar min = std::numeric_limits<t_scalar>::infinity();
    t_scalar max = 0.0;
    if(spdr.get_r() < min) min = spdr.get_r();
    if(spdr.get_r() > max) max = spdr.get_r();
    if(spdr.get_g() < min) min = spdr.get_g();
    if(spdr.get_g() > max) max = spdr.get_g();
    if(spdr.get_b() < min) min = spdr.get_b();
    if(spdr.get_b() > max) max = spdr.get_b();
    t_scalar sum = min+max;
    return s_spd_radiance(sum - spdr.get_r(), sum - spdr.get_g(), sum - spdr.get_b());
    */
    return spdr;
}

//// EOF ////
