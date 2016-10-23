// Filename:    intersection.h
// Author:      Adam Hadar, anh2130
// Purpose:     Definitions for intersections for a simple raytracer.
// Edited:      2016-10-23

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
    s_intersect(void): _is_true(false) {}
    s_intersect(const t_scalar& s, const s_geo_point& gp, const s_geo_vector& gv, const t_uint& u, const t_surface& ts):
        _is_true(true),
        _t(s),
        _point(gp),
        _normal(gv),
        _material(u),
        _surf_type(ts) {}
    
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
    t_surface get_surf_type(void) const
    {
        return _surf_type;
    }
};

//// EOF ////
