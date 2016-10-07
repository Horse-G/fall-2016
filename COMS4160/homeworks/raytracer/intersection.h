/*
 * Filename:    intersection.h
 * Author:      Adam Hadar, anh2130
 * Purpose:     Definitions for intersections for a simple raytracer.
 * Edited:      2016-10-06
 */

//************************************************************************
// Intersection
//************************************************************************
struct s_intersect
{
    bool is_true;
    t_scalar t;
    s_geo_point point;
    s_geo_vector normal;
    t_uint mat_ptr;
    // constructors
    s_intersect(): is_true(false) {}
    s_intersect(t_scalar _t, s_geo_point _pt, s_geo_vector _norm, t_uint _ptr):
        is_true(true),
        t(_t),
        point(_pt),
        normal(_norm),
        mat_ptr(_ptr) {}
};

//// EOF ////
