// Filename:    color.cc
// Author:      Adam Hadar, anh2130
// Purpose:     Definitions for materials in a simple raytracer.
// Edited:      2016-10-27

#include "common.h"
#include "color.h"

//******************************************************************************
// STRUCT_SPD_RADIANCE
//******************************************************************************
// constructors
s_spd_radiance::s_spd_radiance(void){}
s_spd_radiance::s_spd_radiance(const t_scalar& s1, const t_scalar& s2, const t_scalar& s3)
{
    _rgb[0] = s1;
    _rgb[1] = s2;
    _rgb[2] = s3;
}
s_spd_radiance::s_spd_radiance(const s_spd_radiance& spdr)
{
    _rgb[0] = spdr._rgb[0];
    _rgb[1] = spdr._rgb[1];
    _rgb[2] = spdr._rgb[2];
}
   
// get contents
t_scalar s_spd_radiance::get_r(void) const
{
    return _rgb[0];
}
t_scalar s_spd_radiance::get_g(void) const
{
    return _rgb[1];
}
t_scalar s_spd_radiance::get_b(void) const
{
    return _rgb[2];
}

// color operations
//   - addition
//   - subtraction
//   - multiplication
//   - increment assignemnt
s_spd_radiance s_spd_radiance::operator +(const s_spd_radiance& spdr) const
{
    return s_spd_radiance(_rgb[0] + spdr._rgb[0], _rgb[1] + spdr._rgb[1], _rgb[2] + spdr._rgb[2]);
}
s_spd_radiance s_spd_radiance::operator -(const s_spd_radiance& spdr) const
{
    return s_spd_radiance(_rgb[0] - spdr._rgb[0], _rgb[1] - spdr._rgb[1], _rgb[2] - spdr._rgb[2]);
}
s_spd_radiance s_spd_radiance::operator *(const s_spd_radiance& spdr) const
{
    return s_spd_radiance(_rgb[0] * spdr._rgb[0], _rgb[1] * spdr._rgb[1], _rgb[2] * spdr._rgb[2]);
}
s_spd_radiance& s_spd_radiance::operator +=(const s_spd_radiance& spdr)
{
    _rgb[0] += spdr._rgb[0];
    _rgb[1] += spdr._rgb[1];
    _rgb[2] += spdr._rgb[2];
    return *this;
}

// scalar operations
//   - multiplication
//   - division
//   - greater than
s_spd_radiance s_spd_radiance::operator *(const t_scalar& s) const
{
    return s_spd_radiance(_rgb[0] * s, _rgb[1] * s, _rgb[2] * s);
}
s_spd_radiance s_spd_radiance::operator /(const t_scalar& s) const
{
    return s_spd_radiance(_rgb[0] / s, _rgb[1] / s, _rgb[2] / s);
}
bool s_spd_radiance::operator >(const t_scalar& s) const
{
    return _rgb[0] > s && _rgb[1] > s && _rgb[2] > s;
}

//// EOF ////
