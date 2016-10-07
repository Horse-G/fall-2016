/*
 * Filename:    intersection.h
 * Author:      Adam Hadar, anh2130
 * Purpose:     Definitions for intersections for a simple raytracer.
 * Edited:      2016-10-07
 */

//************************************************************************
// Intersection
//************************************************************************
struct s_intersect
{
    //private:
    bool _is_true;
    t_scalar _t;
    s_geo_point _point;
    s_geo_vector _normal;
    t_uint _material;
    
    //public:
    // constructors
    s_intersect(void): _is_true(false) {}
    s_intersect(t_scalar s, s_geo_point gp, s_geo_vector gv, t_uint u):
        _is_true(true),
        _t(s),
        _point(gp),
        _normal(gv),
        _material(u) {}
    
    // destructor
    ~s_intersect(void){}

    // get contents
    bool get_is_true(void) const
    {
        return _is_true;
    }
    t_scalar get_t(void) const
    {
        return _t;
    }
    s_geo_point get_point(void) const
    {
        return _point;
    }
    s_geo_vector get_normal(void) const
    {
        return _normal;
    }
    t_uint get_material(void) const
    {
        return _material;
    }
};

//// EOF ////
