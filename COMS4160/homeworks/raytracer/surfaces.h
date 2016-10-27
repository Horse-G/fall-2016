// Filename:    surfaces.h
// Author:      Adam Hadar, anh2130
// Purpose:     Surface declarations for a simple raytracer.
// Edited:      2016-10-27

#ifndef SURFACES_H
#define SURFACES_H

//*****************************************************************************
// SURFACE
//*****************************************************************************
class c_surface
{
    protected:
    // NOTE: I keep material as the index of the material std::vector
    t_uint    _material;
    t_surface _type;
    
    public:
    // subclass destructor
    virtual ~c_surface(void);
    
    // get content
    t_uint get_material(void);
    t_surface get_type(void);
    
    // subclass find intersection
    virtual s_intersect is_intersect(const s_geo_ray&) =0;
};

//*****************************************************************************
// SURF_PLANE
//*****************************************************************************
class c_surf_plane: public c_surface
{
    private:
    s_geo_vector _normal;
    t_scalar     _distance;
    
    public:
    // constructors
    c_surf_plane(void);
    c_surf_plane(const s_geo_vector&, const t_scalar&, const t_uint&);
    
    // destructor
    virtual ~c_surf_plane(void);
    
    // get contents
    s_geo_vector get_normal(void);
    t_scalar get_distance(void);
    
    // compute intersection
    virtual s_intersect is_intersect(const s_geo_ray&);
};

//*****************************************************************************
// SURF_TRIANGLE
//*****************************************************************************
class c_surf_triangle: public c_surface
{
    private:
    s_geo_point _v[3];
    s_geo_vector _normal;

    public:
    // constructors
    c_surf_triangle(void);
    c_surf_triangle(const s_geo_point&, const s_geo_point&, const s_geo_point&, const t_uint&);

    // destructor
    virtual ~c_surf_triangle(void);

    // get contents
    s_geo_point get_v1(void);
    s_geo_point get_v2(void);
    s_geo_point get_v3(void);
    s_geo_vector get_normal(void);

    // computer intersection
    virtual s_intersect is_intersect(const s_geo_ray&);
};

//*****************************************************************************
// SURF_SPHERE
//*****************************************************************************
class c_surf_sphere: public c_surface
{
    private:
    s_geo_point _origin;
    t_scalar _radius;
    
    public:
    // constructors
    c_surf_sphere(void);
    c_surf_sphere(const s_geo_point&, const t_scalar&, const t_uint&);

    // destructor
    virtual ~c_surf_sphere(void);
    
    // get contents
    s_geo_point get_origin(void);
    t_scalar get_radius(void);

    // find intersection
    virtual s_intersect is_intersect(const s_geo_ray&);
};

#endif
//// EOF ////
