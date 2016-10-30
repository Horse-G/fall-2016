// Filename:    rigging.cc
// Author:      Adam Hadar, anh2130
// Purpose:     Definition of a viewport for a simple raytracer.
// Edited:      2016-10-30

#include "common.h"
#include "geometry.h"
#include "color.h"
#include "viewports.h"
#include "rigging.h"

//******************************************************************************
// RIGGING
//******************************************************************************
s_rig_vps::s_rig_vps(void): _count(0) {}

s_rig_vps::~s_rig_vps(void)
{
    for(t_uint i = 0; i < _count; ++i)
        delete _list[i];
}

void s_rig_vps::set_dimensions(t_scalar& px, t_scalar& py) const
{
    px = 0.0;
    py = 0.0;
    for(t_uint i = 0; i < _count; ++i)
    {
        c_viewport* i_vp = _list[i];
        t_scalar i_px = i_vp->get_px();
        t_scalar i_py = i_vp->get_py();
        px += i_px;
        if(i_py > py)
            py = i_py;
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
