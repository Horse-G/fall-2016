// Geometric objects
class Surface
{
    public:
    uint mat_ptr;
    virtual Intersect find_intersection(const geo_ray &gr) =0;
    virtual void print(void) =0;
};
//
// SURF_PLANE
//
class surf_plane: public Surface
{
    public:
    geo_vector normal;
    scalar dist;
    surf_plane(){}
    surf_plane(geo_vector _n, scalar _d, uint _p):
        normal(_n.norm()),
        dist(_d)
        { mat_ptr = _p; }
    Intersect find_intersection(const geo_ray &gr)
    {
        scalar t;
        scalar dN = gr.dir % normal;
        if(dN < 1e-6)
            return Intersect();
        t = -(gr.origin % normal + dist)/dN;
        return Intersect(t, gr.pos(t), normal, mat_ptr);
    }
    void print(void)
    {
        std::cout<<"    type plane"<<std::endl;
        std::cout<<"    normal "<<normal<<std::endl;
        std::cout<<"    dist "<<dist<<std::endl;
        return;
    }
};

//
// SURF_TRIANGLE
//
class surf_triangle: public Surface
{
    public:
    geo_point v1, v2, v3;
    geo_vector normal;
    surf_triangle(){}
    surf_triangle(geo_point _v1, geo_point _v2, geo_point _v3, uint _p):
        v1(_v1),
        v2(_v2),
        v3(_v3){
        normal = ((v2 - v1) * (v3 - v1)).norm();
        mat_ptr = _p;
    }
    // Moller-Trumbore, ripped from en.wikipedia.org/wiki/Moller-Trumbore_intersection_algorithm
    Intersect find_intersection(const geo_ray &gr)
    {
        geo_vector e1,e2;
        geo_vector P,Q,T;
        scalar det, inv_det, u, v;
        scalar t;
        e1 = v2 - v1;
        e2 = v3 - v1;
        P = gr.dir * e2;
        det = e1 % P;
        if(det > -1e-6 && det < 1e-6)
            return Intersect();
        inv_det = 1.0/det;

        T = gr.origin - v1;
        u = (T % P) * inv_det;
        if(u < 0.0 || u > 1.0)
            return Intersect();

        Q = T * e1;
        v = (gr.dir % Q) * inv_det;
        if(v < 0.0 || u + v > 1.0)
            return Intersect();

        t = (e2 % Q) * inv_det;
        if(t > 1e-6)
            return Intersect(t, gr.pos(t), normal, mat_ptr);
        return Intersect();
    }
    void print(void)
    {
        std::cout<<"    type triangle"<<std::endl;
        std::cout<<"    v1 "<<v1<<std::endl;
        std::cout<<"    v2 "<<v2<<std::endl;
        std::cout<<"    v3 "<<v3<<std::endl;
        return;
    }
};
// END SURF_TRIANGLE

//
// SURF_SPHERE
//
class surf_sphere: public Surface
{
    public:
    geo_point origin;
    scalar r;
    surf_sphere(){}
    surf_sphere(geo_point _origin, scalar _r, int _p):
        origin(_origin),
        r(_r)
        { mat_ptr = _p; }
    Intersect find_intersection(const geo_ray &gr)
    {
        scalar t, _t;
        geo_point pt;

        geo_vector dist = gr.origin - origin;
        scalar a = gr.dir % gr.dir;
        scalar b = gr.dir % dist;
        scalar discrim = b*b - a * (dist % dist - r*r);
        if(discrim < 0)
            return Intersect();
        // graze
        else if (discrim < 1e-6)
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
        return Intersect(t, pt, (origin - pt).norm(), mat_ptr);
    }
    void print(void)
    {
        std::cout<<"    type sphere"<<std::endl;
        std::cout<<"    origin "<<origin<<std::endl;
        std::cout<<"    radius "<<r<<std::endl;
        return;
    }
};
// END SURF_SPHERE


