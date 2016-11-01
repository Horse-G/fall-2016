// Filename:    rigging.cc
// Author:      Adam Hadar, anh2130
// Purpose:     Definition of a viewport for a simple raytracer.
// Edited:      2016-11-01

#include "common.h"
#include "geometry.h"
#include "color.h"
#include "viewports.h"
#include "rigging.h"

//******************************************************************************
// RIGGING
//******************************************************************************
s_rig_vps::s_rig_vps(void): _count(0), _width(1), _height(1) {}

s_rig_vps::~s_rig_vps(void)
{
    for(t_uint i = 0; i < _count; ++i)
        delete _list[i];
}

void s_rig_vps::set_dimensions(t_scalar& px, t_scalar& py)
{
    px = 0.0;
    py = 0.0;
    for(t_uint i = 0; i < _count; ++i)
    {
        c_viewport* i_vp = _list[i];
        t_scalar i_px = i_vp->get_px();
        t_scalar i_py = i_vp->get_py();
        if(i_px > px)
            px = i_px;
        if(i_py > py)
            py = i_py;
    }
    _width = px;
    _height = py;
    if(_count > 1)
        px *= 2.;
    if(_count > 2)
        py *= ceil(_count/2.);
    return;
}
void s_rig_vps::generate_image(Imf::Array2D<Imf::Rgba>& img, const s_scene& scene) const
{
    t_scalar px_start = 0.0;
    t_scalar py_start = 0.0;
    for(t_uint i = 0; i < _count; ++i)
    {
        if(i % 2 == 1)
            px_start = _width;
        if(i % 2 == 0 && i > 0)
        {
            py_start += _height;
            px_start = 0.0;
        }
        c_viewport* i_vp = _list[i];
        t_scalar px_end = i_vp->get_px();
        t_scalar py_end = i_vp->get_py();
        i_vp->generate_subimage(img, px_start, px_start + px_end, py_start, py_start + py_end, scene);
    }
    return;
}

c_viewport* s_rig_vps::get_vp(const t_uint& i) const
{
    return _list[i];
}
t_uint s_rig_vps::get_count(void) const
{
    return _count;
}

//// EOF ////
