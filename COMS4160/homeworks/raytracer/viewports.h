// Filename:    viewports.h
// Author:      Adam Hadar, anh2130
// Purpose:     Declaration of a viewport for a simple raytracer.
// Edited:      2016-10-30

#ifndef VIEWPORTS_H
#define VIEWPORTS_H

//******************************************************************************
// VIEWPORT
//******************************************************************************
class c_viewport
{
    protected:
    s_geo_point  _eye;
    t_scalar     _fl;
    s_geo_vector _uvw[3];
    t_uint       _ix, _iy;
    t_scalar     _px, _py;

    public:
    // subclass destructor
    virtual ~c_viewport(void);

    // get contents
    s_geo_point get_eye(void) const;
    s_geo_vector get_u(void) const;
    s_geo_vector get_v(void) const;
    s_geo_vector get_w(void) const;
    t_scalar get_fl(void) const;
    t_uint get_ix(void) const;
    t_uint get_iy(void) const;
    t_uint get_px(void) const;
    t_uint get_py(void) const;
    
    // subclass filter pixel
    virtual s_spd_radiance filter(const s_spd_radiance&) const =0;
};

//******************************************************************************
// VIEWPORT_DEFAULT
//******************************************************************************
class c_vp_default: public c_viewport
{
    public:
    c_vp_default(void);
    c_vp_default(const s_geo_point&, const s_geo_vector&, const t_scalar&, const t_uint&, const t_uint&, const t_scalar&, const t_scalar&);
    virtual ~c_vp_default(void);

    virtual s_spd_radiance filter(const s_spd_radiance&) const;
};

#endif
//// EOF ////
