/*
 * Filename:    geometry.h
 * Author:      Adam Hadar, anh2130
 * Purpose:     Definitions for vectors, points, and rays for a simple raytracer.
 * Edited:      2016-10-06
 */

//************************************************************************
// GEO_VECTOR
//************************************************************************
struct s_geo_vector
{
    t_scalar x,y,z;
    
    // Constructor
    s_geo_vector(){}
    s_geo_vector(t_scalar _x, t_scalar _y, t_scalar _z): x(_x), y(_y), z(_z) {}
    s_geo_vector(const s_geo_vector &v) : x(v.x), y(v.y), z(v.z) {}
    // cross product
    s_geo_vector operator *(const s_geo_vector &gv) const
    {
        return s_geo_vector(y*gv.z - z*gv.y, z*gv.x - x*gv.z, x*gv.y - y*gv.x);
    }
    // dot product
    //// we'll pretend the actual modulo doesn't exist
    t_scalar operator %(const s_geo_vector &gv) const
    {
        return x*gv.x + y*gv.y + z*gv.z;
    }
    s_geo_vector operator *(t_scalar multi) const
    {
        return s_geo_vector(x*multi, y*multi, z*multi);
    }
    s_geo_vector operator +(const s_geo_vector &gv) const
    {
        return s_geo_vector(x+gv.x, y+gv.y, z+gv.z);
    }
    s_geo_vector operator -(const s_geo_vector &gv) const
    {
        return s_geo_vector(x-gv.x, y-gv.y, z-gv.z);
    }
    s_geo_vector operator -(void) const
    {
        return s_geo_vector(-x,-y,-z);
    }
    s_geo_vector operator /(t_scalar divisor) const
    {
        return s_geo_vector(x/divisor, y/divisor, z/divisor);
    }
    s_geo_vector norm() const
    {
        return *this / sqrt(x*x + y*y + z*z);
    }
};
inline std::ostream& operator<<(std::ostream& os, const s_geo_vector& gv)
{
    return os <<"<" <<gv.x <<"," <<gv.y <<"," <<gv.z <<">";
}
inline std::istream& operator>>(std::istream& is, s_geo_vector& gv)
{
    return is >>gv.x >>gv.y >>gv.z;
}

//************************************************************************
// GEO_POINT
//************************************************************************
struct s_geo_point
{
    t_scalar x,y,z;
    
    // Constructors
    s_geo_point(){}
    s_geo_point(t_scalar _x, t_scalar _y, t_scalar _z) : x(_x), y(_y), z(_z) {}
    s_geo_point(const s_geo_point &gp) : x(gp.x), y(gp.y), z(gp.z) {}
   
    // cross product with geo_vector
    t_scalar operator %(const s_geo_vector &gv) const
    {
        return x*gv.x + y*gv.y + z*gv.z;
    }
    s_geo_vector operator +(const s_geo_point &gp) const
    {
        return s_geo_vector(x + gp.x, y + gp.y, z + gp.z);
    }
    s_geo_vector operator -(const s_geo_point &gp) const
    {
        return s_geo_vector(x - gp.x, y - gp.y, z - gp.z);
    }
};
inline std::ostream& operator<<(std::ostream& os, const s_geo_point& gp)
{
    return os <<"[" <<gp.x <<"," <<gp.y <<"," <<gp.z <<"]";
}
inline std::istream& operator>>(std::istream& is, s_geo_point& gp)
{
    return is >>gp.x >>gp.y >>gp.z;
}

//************************************************************************
// GEO_RAY
//************************************************************************
struct s_geo_ray
{
    s_geo_point origin;
    s_geo_vector dir;
    // Constructors
    s_geo_ray(){}
    s_geo_ray(s_geo_point _origin, s_geo_vector _dir): origin(_origin), dir(_dir.norm()) {}

    s_geo_ray operator +(const s_geo_ray &r) const
    {
        return s_geo_ray(origin, dir+r.dir);
    }
    s_geo_ray operator -(const s_geo_ray &r) const
    {
        return s_geo_ray(origin, dir - r.dir);
    }
    // cross product
    s_geo_ray operator *(const s_geo_ray &r) const
    {
        return s_geo_ray(origin, dir * r.dir);
    }
    s_geo_point pos(t_scalar _pos) const
    {
        s_geo_point out = origin;
        out.x += dir.x * _pos;
        out.y += dir.y * _pos;
        out.z += dir.z * _pos;
        return out;
    }
};
inline std::ostream& operator<<(std::ostream& os, const s_geo_ray& gr)
{
    return os
        <<"Ray"                 <<std::endl
        <<"origin " <<gr.origin <<std::endl
        <<"direct " <<gr.dir    <<std::endl;
}

//// EOF ////
