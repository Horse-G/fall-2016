/*
 * Filename:    h_surfaces.h
 * Author:      Adam Hadar, anh2130
 * Purpose:     Surface definitions for a simple raytracer.
 * Edited:      2016-10-06
 */

//************************************************************************
// SURFACE
//************************************************************************
class c_surface
{
    public:
    uint mat_ptr;
    virtual s_intersect find_intersection(const s_geo_ray &gr) =0;
    virtual void print(const char* tab) =0;
};

//************************************************************************
// SURF_PLANE
//************************************************************************
class c_surf_plane: public c_surface
{
    public:
    s_geo_vector normal;
    t_scalar dist;
    c_surf_plane(){}
    c_surf_plane(s_geo_vector _n, t_scalar _d, t_uint _p):
        normal(_n.norm()),
        dist(_d)
        { mat_ptr = _p; }
    s_intersect find_intersection(const s_geo_ray &gr)
    {
        t_scalar t;
        t_scalar dN = gr.dir % normal;
        if(dN < EPSILON)
            return s_intersect();
        t = -(gr.origin % normal + dist)/dN;
        return s_intersect(t, gr.pos(t), normal, mat_ptr);
    }
    void print(const char* tab)
    {
        std::cout
            <<tab <<"type "   <<"plane" <<std::endl
            <<tab <<"normal " <<normal  <<std::endl
            <<tab <<"dist "   <<dist    <<std::endl;
        return;
    }
};

//************************************************************************
// SURF_TRIANGLE
//************************************************************************
class c_surf_triangle: public c_surface
{
    public:
    s_geo_point v1, v2, v3;
    s_geo_vector normal;
    c_surf_triangle(){}
    c_surf_triangle(s_geo_point _v1, s_geo_point _v2, s_geo_point _v3, t_uint _p):
        v1(_v1),
        v2(_v2),
        v3(_v3){
        normal = ((v2 - v1) * (v3 - v1)).norm();
        mat_ptr = _p;
    }
    // Moller-Trumbore, ripped from en.wikipedia.org/wiki/Moller-Trumbore_intersection_algorithm
    s_intersect find_intersection(const s_geo_ray &gr)
    {
        s_geo_vector e1,e2;
        s_geo_vector P,Q,T;
        t_scalar det, inv_det, u, v;
        t_scalar t;
        e1 = v2 - v1;
        e2 = v3 - v1;
        P = gr.dir * e2;
        det = e1 % P;
        if(abs(det) < EPSILON)
            return s_intersect();
        inv_det = 1.0/det;

        T = gr.origin - v1;
        u = (T % P) * inv_det;
        if(u < 0.0 || u > 1.0)
            return s_intersect();

        Q = T * e1;
        v = (gr.dir % Q) * inv_det;
        if(v < 0.0 || u + v > 1.0)
            return s_intersect();

        t = (e2 % Q) * inv_det;
        if(t > EPSILON)
            return s_intersect(t, gr.pos(t), normal, mat_ptr);
        return s_intersect();
    }
    void print(const char* tab)
    {
        std::cout
            <<tab <<"type " <<"triangle" <<std::endl
            <<tab <<"v1 "   <<v1         <<std::endl
            <<tab <<"v2 "   <<v2         <<std::endl
            <<tab <<"v3 "   <<v3         <<std::endl;
        return;
    }
};

//************************************************************************
// SURF_SPHERE
//************************************************************************
class c_surf_sphere: public c_surface
{
    public:
    s_geo_point origin;
    t_scalar r;
    c_surf_sphere(){}
    c_surf_sphere(s_geo_point _origin, t_scalar _r, t_uint _p):
        origin(_origin),
        r(_r)
        { mat_ptr = _p; }
    s_intersect find_intersection(const s_geo_ray &gr)
    {
        t_scalar t, _t;
        s_geo_point pt;

        s_geo_vector dist = gr.origin - origin;
        t_scalar a = gr.dir % gr.dir;
        t_scalar b = gr.dir % dist;
        t_scalar discrim = b*b - a * (dist % dist - r*r);
        if(discrim < 0)
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
        return s_intersect(t, pt, (origin - pt).norm(), mat_ptr);
    }
    void print(const char* tab)
    {
        std::cout
            <<tab <<"type "   <<"sphere" <<std::endl
            <<tab <<"origin " <<origin   <<std::endl
            <<tab <<"radius " <<r        <<std::endl;
        return;
    }
};

//// EOF ////
