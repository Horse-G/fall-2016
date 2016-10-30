// Filename:    surfaces.cc
// Author:      Adam Hadar, anh2130
// Purpose:     Definitions of surfaces for a simple raytracer.
// Edited:      2016-10-30

#include "common.h"
#include "geometry.h"
#include "intersection.h"
#include "surfaces.h"

//*****************************************************************************
// SURFACE
//*****************************************************************************
// subclass destructor
c_surface::~c_surface(void) {}
    
// get content
t_uint c_surface::get_material(void)
{
    return _material;
}
t_surface c_surface::get_type(void)
{
    return _type;
}

//*****************************************************************************
// SURF_PLANE
//*****************************************************************************
// constructors
c_surf_plane::c_surf_plane(void)
{
    _type = PLANE;
}
c_surf_plane::c_surf_plane(const s_geo_vector& gv, const t_scalar& s, const t_uint& u):
    _normal(-gv.norm()),
    _distance(-s)
{
    _material = u;
    _type = PLANE;
}
    
// destructor
c_surf_plane::~c_surf_plane(void){}
    
// get contents
s_geo_vector c_surf_plane::get_normal(void)
{
    return _normal;
}
t_scalar c_surf_plane::get_distance(void)
{
    return _distance;
}
    
// compute intersection
s_intersect c_surf_plane::is_intersect(const s_geo_ray& gr)
{
    t_scalar t;
    t_scalar dN = gr.get_direction() % _normal;
    
    //if(abs(dN) < EPSILON)
    //    return s_intersect(); 
    //if(dN <= 0.0)
    //   return s_intersect();

    t = (_distance - gr.get_origin() % _normal)/dN;
    if(dN < 0.0)
        return s_intersect(t, gr.pos(t), -_normal, 0, _type);
    return s_intersect(t, gr.pos(t), _normal, _material, _type);
}

//*****************************************************************************
// SURF_TRIANGLE
//*****************************************************************************
// constructors
c_surf_triangle::c_surf_triangle(void)
{
    _type = TRIANGLE;
}
c_surf_triangle::c_surf_triangle(const s_geo_point& gp1, const s_geo_point& gp2, const s_geo_point& gp3, const t_uint& u)
{
    _v[0] = gp1;
    _v[1] = gp2;
    _v[2] = gp3;
    _normal = -((_v[1] - _v[0]) * (_v[2] - _v[1])).norm();
    _material = u;
    _type = TRIANGLE;
}

// destructor
c_surf_triangle::~c_surf_triangle(void){}

// get contents
s_geo_point c_surf_triangle::get_v1(void)
{
    return _v[0];
}
s_geo_point c_surf_triangle::get_v2(void)
{
    return _v[1];
}
s_geo_point c_surf_triangle::get_v3(void)
{
    return _v[2];
}
s_geo_vector c_surf_triangle::get_normal(void)
{
    return _normal;
}

// computer intersection
// Moller-Trumbore
//   ripped from en.wikipedia.org/wiki/Moller-Trumbore_intersection_algorithm
s_intersect c_surf_triangle::is_intersect(const s_geo_ray& gr)
{
    // memory allocation
    s_geo_vector e1,e2;
    s_geo_vector P,Q,T;
    t_scalar det, inv_det, u, v;
    t_scalar t;
        
    e1 = _v[1] - _v[0];
    e2 = _v[2] - _v[0];
    P = gr.get_direction() * e2;
    det = e1 % P;
    if(abs(det) < EPSILON)
        return s_intersect();
    inv_det = 1.0/det;
    T = gr.get_origin() - _v[0];
    u = (T % P) * inv_det;
    if(u < 0.0 || u > 1.0)
        return s_intersect();
    Q = T * e1;
    v = (gr.get_direction() % Q) * inv_det;
    if(v < 0.0 || u + v > 1.0)
        return s_intersect();
    t = (e2 % Q) * inv_det;
    if(t > EPSILON)
    {
        if (_normal % gr.get_direction() < 0.0)
            return s_intersect(t, gr.pos(t), -_normal, 0, _type);
        return s_intersect(t, gr.pos(t), _normal, _material, _type);
    }
    return s_intersect();
}

//*****************************************************************************
// SURF_SPHERE
//*****************************************************************************
// constructors
c_surf_sphere::c_surf_sphere(void)
{
    _type = SPHERE;
}
c_surf_sphere::c_surf_sphere(const s_geo_point& gp, const t_scalar& s, const t_uint& u):
    _origin(gp),
    _radius(s)
{
    _material = u;
    _type = SPHERE;
}

// destructor
c_surf_sphere::~c_surf_sphere(void){}
    
// get contents
s_geo_point c_surf_sphere::get_origin(void)
{
    return _origin;
}
t_scalar c_surf_sphere::get_radius(void)
{
    return _radius;
}

// find intersection
s_intersect c_surf_sphere::is_intersect(const s_geo_ray& gr)
{
    // memory allocation
    t_scalar t, _t;
    s_geo_point pt;
    s_geo_point gr_origin = gr.get_origin();
    s_geo_vector gr_direction = gr.get_direction();

    s_geo_vector dist = gr_origin - _origin;
    t_scalar a = gr_direction % gr_direction;
    t_scalar b = gr_direction % dist;
    t_scalar discrim = b*b - a * (dist % dist - _radius*_radius);
    if(discrim < 0.0)
        return s_intersect();
    // graze
    else if (discrim < EPSILON)
    {
        t = (-b - sqrt(discrim))/a;
    }
    else
    {
        t = -b/a;
        _t = sqrt(discrim)/a;
        if (t - _t < t + _t)
            t -= _t;
        else
            t += _t;
    }
    pt = gr.pos(t);
    return s_intersect(t, pt, (_origin - pt).norm(), _material, _type);
}

//// EOF ////
