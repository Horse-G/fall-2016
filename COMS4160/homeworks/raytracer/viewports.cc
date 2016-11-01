// Filename:    viewports.cc
// Author:      Adam Hadar, anh2130
// Purpose:     Definition of a viewport for a simple raytracer.
// Edited:      2016-11-01

#include "common.h"
#include "geometry.h"
#include "intersection.h"
#include "surfaces.h"
#include "color.h"
#include "lights.h"
#include "materials.h"
#include "viewports.h"
#include "scene.h"
#include "raytrace.h"

//******************************************************************************
// VIEWPORT
//******************************************************************************
// constructor
c_viewport::c_viewport(void){}
c_viewport::c_viewport(
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
c_viewport::~c_viewport(void){}

void c_viewport::generate_subimage(
    Imf::Array2D<Imf::Rgba>& img_pixels,
    const t_scalar& px_start, const t_scalar& px_end,
    const t_scalar& py_start, const t_scalar& py_end,
    const s_scene& scene)
{
    // pixel step, center of viewport
    t_scalar d_x = _ix / (px_end - px_start);
    t_scalar d_y = _iy / (py_end - py_start);
    t_scalar o_x = (px_end + px_start + 1.) / 2.;
    t_scalar o_y = (py_end + py_start + 1.) / 2.;

    // iterate through pixels
    for(t_uint y = py_start; y < py_end; ++y)
    for(t_uint x = px_start; x < px_end; ++x)
    {
        // generate data
        Imf::Rgba* i_pxl = &img_pixels[y][x];
        s_spd_radiance i_clr = filter(
            compute_L(
                s_geo_ray(
                    _eye,
                    _uvw[0] * d_x * (x - o_x)
                    + _uvw[1] * d_y * (o_y - y)
                    - _uvw[2] * _fl
                ),
                scene,
                20,
                _fl, std::numeric_limits<t_scalar>::infinity(),
                PRIMARY,
                c_light_point()
            )
        );
        // store color
        i_pxl->r = i_clr.get_r();
        i_pxl->g = i_clr.get_g();
        i_pxl->b = i_clr.get_b();
        i_pxl->a = 1.0;
    }
    return;
}

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
): c_viewport(gp,gv,s1,u1,u2,s2,s3) {}

// destructor
c_vp_default::~c_vp_default(void){}

s_spd_radiance c_vp_default::filter(const s_spd_radiance& spdr) const
{
    return spdr;
}

//******************************************************************************
// VIEWPORT_RED
//******************************************************************************
c_vp_red::c_vp_red(void){}
c_vp_red::c_vp_red(
    const s_geo_point& gp,
    const s_geo_vector& gv,
    const t_scalar& s1,
    const t_uint& u1,
    const t_uint& u2,
    const t_scalar& s2,
    const t_scalar& s3
): c_viewport(gp,gv,s1,u1,u2,s2,s3) {}

// destructor
c_vp_red::~c_vp_red(void){}

s_spd_radiance c_vp_red::filter(const s_spd_radiance& spdr) const
{
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
}

//******************************************************************************
// VIEWPORT_GREEN
//******************************************************************************
c_vp_green::c_vp_green(void){}
c_vp_green::c_vp_green(
    const s_geo_point& gp,
    const s_geo_vector& gv,
    const t_scalar& s1,
    const t_uint& u1,
    const t_uint& u2,
    const t_scalar& s2,
    const t_scalar& s3
): c_viewport(gp,gv,s1,u1,u2,s2,s3) {}

// destructor
c_vp_green::~c_vp_green(void){}

s_spd_radiance c_vp_green::filter(const s_spd_radiance& spdr) const
{
    t_scalar green = 0.2126*spdr.get_r() + 0.7152*spdr.get_g() + 0.0722*spdr.get_b();
    return s_spd_radiance(0.0,green,0.0);
}

//******************************************************************************
// VIEWPORT_BLUE
//******************************************************************************
c_vp_blue::c_vp_blue(void){}
c_vp_blue::c_vp_blue(
    const s_geo_point& gp,
    const s_geo_vector& gv,
    const t_scalar& s1,
    const t_uint& u1,
    const t_uint& u2,
    const t_scalar& s2,
    const t_scalar& s3
): c_viewport(gp,gv,s1,u1,u2,s2,s3) {}

// destructor
c_vp_blue::~c_vp_blue(void){}

s_spd_radiance c_vp_blue::filter(const s_spd_radiance& spdr) const
{
    t_scalar blue = 0.2126*spdr.get_r() + 0.7152*spdr.get_g() + 0.0722*spdr.get_b();
    return s_spd_radiance(0.0,0.0,blue);
}

//// EOF ////
