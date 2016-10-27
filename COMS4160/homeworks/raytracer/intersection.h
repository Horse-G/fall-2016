// Filename:    intersection.h
// Author:      Adam Hadar, anh2130
// Purpose:     Declarations for intersections for a simple raytracer.
// Edited:      2016-10-27

#ifndef INTERSECTION_H
#define INTERSECTION_H

//******************************************************************************
// STRUCT_INTERSECTION
//******************************************************************************
struct s_intersect
{
    //private:
    bool         _is_true;
    t_scalar     _t;
    s_geo_point  _point;
    s_geo_vector _normal;
    t_uint       _material;
    t_surface    _surf_type;
    
    //public:
    // constructors
    s_intersect(void);
    s_intersect(const t_scalar&, const s_geo_point&, const s_geo_vector&, const t_uint&, const t_surface&);
    s_intersect(const t_scalar&);

    // destructor
    ~s_intersect(void);

    // get contents
    bool get_is_true(void) const;
    t_scalar get_t(void) const;
    s_geo_point get_point(void) const;
    s_geo_vector get_normal(void) const;
    t_uint get_material(void) const;
    t_surface get_surf_type(void) const;
};

#endif
//// EOF ////
