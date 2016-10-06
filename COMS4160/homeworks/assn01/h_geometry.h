//
// GEO_VECTOR
//
struct geo_vector
{
    scalar x,y,z;
    
    // Constructor
    geo_vector(){}
    geo_vector(scalar _x, scalar _y, scalar _z): x(_x), y(_y), z(_z) {}
    geo_vector(const geo_vector &v) : x(v.x), y(v.y), z(v.z) {}
    // cross product
    geo_vector operator *(const geo_vector &gv) const
    {
        return geo_vector(y*gv.z - z*gv.y, z*gv.x - x*gv.z, x*gv.y - y*gv.x);
    }
    // dot product
    //// we'll pretend the actual modulo doesn't exist
    scalar operator %(const geo_vector &gv) const
    {
        return x*gv.x + y*gv.y + z*gv.z;
    }
    geo_vector operator *(scalar multi) const
    {
        return geo_vector(x*multi, y*multi, z*multi);
    }
    geo_vector operator +(const geo_vector &gv) const
    {
        return geo_vector(x+gv.x, y+gv.y, z+gv.z);
    }
    geo_vector operator -(const geo_vector &gv) const
    {
        return geo_vector(x-gv.x, y-gv.y, z-gv.z);
    }
    geo_vector operator -(void) const
    {
        return geo_vector(-x,-y,-z);
    }
    geo_vector operator /(scalar divisor) const
    {
        return geo_vector(x/divisor, y/divisor, z/divisor);
    }
    geo_vector norm() const
    {
        return *this / sqrt(x*x + y*y + z*z);
    }
    };// i/o
    inline std::ostream& operator<<(std::ostream& os, const geo_vector& gv)
        {return os<<"<"<<gv.x<<","<<gv.y<<","<<gv.z<<">";}
    inline std::istream& operator>>(std::istream& is, geo_vector& gv)
        {return is>>gv.x>>gv.y>>gv.z;}
// END GEO_VECTOR

//
// GEO_POINT
//
struct geo_point
{
    scalar x,y,z;
    
    // Constructors
    geo_point(){}
    geo_point(scalar _x, scalar _y, scalar _z) : x(_x), y(_y), z(_z) {}
    geo_point(const geo_point &gp) : x(gp.x), y(gp.y), z(gp.z) {}
   
    // cross product with geo_vector
    double operator %(const geo_vector &gv) const
    {
        return x*gv.x + y*gv.y + z*gv.z;
    }
    geo_vector operator +(const geo_point &gp) const
    {
        return geo_vector(x + gp.x, y + gp.y, z + gp.z);
    }
    geo_vector operator -(const geo_point &gp) const
    {
        return geo_vector(x - gp.x, y - gp.y, z - gp.z);
    }
    };// i/o
    inline std::ostream& operator<<(std::ostream& os, const geo_point& gp)
        {return os<<"["<<gp.x<<","<<gp.y<<","<<gp.z<<"]";}
    inline std::istream& operator>>(std::istream& is, geo_point& gp)
        {return is>>gp.x>>gp.y>>gp.z;}
// END GEO_POINT

//
// GEO_RAY
//
struct geo_ray
{
    geo_point origin;
    geo_vector dir;
    // Constructors
    geo_ray(){}
    geo_ray(geo_point _origin, geo_vector _dir): origin(_origin), dir(_dir.norm()) {}

    geo_ray operator +(const geo_ray &r) const
    {
        return geo_ray(origin, dir+r.dir);
    }
    geo_ray operator -(const geo_ray &r) const
    {
        return geo_ray(origin, dir - r.dir);
    }
    // cross product
    geo_ray operator *(const geo_ray &r) const
    {
        return geo_ray(origin, dir * r.dir);
    }
    geo_point pos(scalar _pos) const
    {
        geo_point out = origin;
        out.x += dir.x * _pos;
        out.y += dir.y * _pos;
        out.z += dir.z * _pos;
        return out;
    }
    };// i/o
    inline std::ostream& operator<<(std::ostream& os, const geo_ray& gr)
    {
        return os<<"Ray"<<std::endl
            <<"origin "<<gr.origin<<std::endl
            <<"direct "<<gr.dir<<std::endl;
    }
//END GEO_RAY

// Camera
struct Viewport
{
    geo_point eye;
    scalar fl;
    geo_vector u, v, w;
    uint img_x, img_y;
    scalar pix_x, pix_y;

    Viewport(){}
    Viewport(geo_point _eye, geo_vector dir, scalar _fl, uint _ix, uint _iy, scalar _px, scalar _py):
        eye(_eye),
        fl(_fl),
        img_x(_ix),
        img_y(_iy),
        pix_x(_px),
        pix_y(_py)
    {
        u = dir * geo_vector(0.0,1.0,0.0);
        v = u * dir;
        w = -dir;
        u = u.norm();
        v = v.norm();
        w = w.norm();
    }
};

// Intersection
struct Intersect
{
    bool yes_no;
    scalar t;
    geo_point point;
    geo_vector normal;
    uint mat_ptr;
    // constructors
    Intersect(): yes_no(false) {}
    Intersect(scalar _t, geo_point _pt, geo_vector _norm, uint _ptr):
        yes_no(true),
        t(_t),
        point(_pt),
        normal(_norm),
        mat_ptr(_ptr) {}
};

















