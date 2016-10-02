// wooo geometry

#include <math.h>

struct geo_vector
{
    double x,y,z;
    
    // Constructor
    geo_vector(){}
    geo_vector(double _x, double _y, double _z): x(_x), y(_y), z(_z) {}
    geo_vector(const geo_vector &v) : x(v.x), y(v.y), z(v.z) {}

    // cross product
    geo_vector operator *(const geo_vector &v) const
    {
        //return geo_vector(5.0,6.0,7.0);
        return geo_vector(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x);
    }
    // dot product
    //// we'll pretend the actual modulo doesn't exist
    double operator %(const geo_vector &v) const
    {
        return x*v.x + y*v.y + z*v.z;
    }
    geo_vector operator *(double multi) const
    {
        return geo_vector(x*multi, y*multi, z*multi);
    }
    geo_vector operator +(const geo_vector &v) const
    {
        return geo_vector(x+v.x, y+v.y, z+v.z);
    }
    geo_vector operator -(const geo_vector &v) const
    {
        return geo_vector(x-v.x, y-v.y, z-v.z);
    }
    geo_vector operator /(double divisor) const
    {
        return geo_vector(x/divisor, y/divisor, z/divisor);
    }
    geo_vector norm() const
    {
        return *this / sqrt(x*x + y*y + z*z);
    }
};
struct geo_point
{
    double x,y,z;
    
    // Constructors
    geo_point(){}
    geo_point(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}
    geo_point(const geo_point &p) : x(p.x), y(p.y), z(p.z) {}
   
    geo_vector operator +(const geo_point &p) const
    {
        return geo_vector(x + p.x, y + p.y, z + p.z);
    }
    geo_vector operator -(const geo_point &p) const
    {
        return geo_vector(x - p.x, y - p.y, z - p.z);
    }
};

struct Ray
{
    geo_point origin;
    geo_vector dir;
    // Constructors
    Ray(){}
    Ray(geo_point _origin, geo_vector _dir): origin(_origin), dir(_dir.norm()) {}

    Ray operator +(const Ray &r) const
    {
        return Ray(origin, dir+r.dir);
    }
    Ray operator -(const Ray &r) const
    {
        return Ray(origin, dir - r.dir);
    }
    // cross product
    Ray operator *(const Ray &r) const
    {
        return Ray(origin, dir * r.dir);
    }
    geo_point pos(double _pos) const
    {
        geo_point out = origin;
        out.x += dir.x * _pos;
        out.y += dir.y * _pos;
        out.z += dir.z * _pos;
        return out;
    }
};

// Camera
struct Viewport
{
    geo_point eye;
    double fl;
    geo_vector u, v, w;
    int pixel_x, pixel_y;
    double img_x, img_y;

    Viewport(){}
    Viewport(geo_point _eye, geo_vector dir, double _fl, int _ix, int _iy, double _px, double _py):
        eye(_eye),
        fl(_fl),
        pixel_x(_px),
        pixel_y(_py),
        img_x(_ix),
        img_y(_iy)
    {
        u = dir * geo_vector(0.0,1.0,0.0);
        v = u * dir;
        w = geo_vector(-dir.x, -dir.y, -dir.z);
        u = u.norm();
        v = v.norm();
        w = w.norm();
    }
};

// Intersection
struct Intersect
{
    bool yes_no;
    double t;
    geo_point point;
    geo_vector normal;
    int mat_ptr;
    // constructors
    Intersect(): yes_no(false) {}
    Intersect(double _t, geo_point _pt, geo_vector _norm, int _ptr):
        yes_no(true),
        t(_t),
        point(_pt),
        normal(_norm),
        mat_ptr(_ptr) {}
};

// Geometric objects
class Object
{
    public:
    virtual Intersect find_intersection(const Ray &r) =0;
    int mat_ptr;
};

class Sphere: public Object
{
    private:
    geo_point origin;
    float r;
    
    public:
    Sphere(){}
    Sphere(geo_point _origin, float _r, int _ptr):
        origin(_origin),
        r(_r)
        { mat_ptr = _ptr; }
    Intersect find_intersection(const Ray &ray)
    {
        double t;
        double _t;
        geo_point pt;

        geo_vector dist = ray.origin - origin;
        double a = ray.dir % ray.dir;
        double b = ray.dir % dist;
        double discrim = b*b - a * (dist % dist - r*r);
        if(discrim < 0)
            return Intersect();
        // graze
        else if (discrim < 0.001)
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
        pt = ray.pos(t);
        return Intersect(t, pt, (origin - pt).norm(), mat_ptr);
    }
};






















