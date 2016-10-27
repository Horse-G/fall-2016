// Filename:    geometry.h
// Author:      Adam Hadar, anh2130
// Purpose:     Declarations for vectors, points, and rays for a simple raytracer.
// Edited:      2016-10-27

#ifndef GEOMETRY_H
#define GEOMETRY_H

//******************************************************************************
// GEO_VECTOR
//******************************************************************************
struct s_geo_vector
{
    // friends only to geo structs
    friend struct s_geo_point;
    friend struct s_geo_ray;
    
    private:
    t_scalar _xyz[3];
    
    public:
    // constructors
    s_geo_vector(void);
    s_geo_vector(const t_scalar&, const t_scalar&, const t_scalar&);
    s_geo_vector(const s_geo_vector&);
    
    // destructor
    ~s_geo_vector(void);

    // get contents
    t_scalar get_x(void) const;
    t_scalar get_z(void) const;

    // vector operations
    //   - cross product
    //   - dot product
    //   - addition
    //   - subtraction
    s_geo_vector operator *(const s_geo_vector&) const;
    t_scalar operator %(const s_geo_vector&) const;
    s_geo_vector operator +(const s_geo_vector&) const;
    s_geo_vector operator -(const s_geo_vector&) const;

    // scalar operations
    //   - multiplication
    //   - negation
    //   - division
    s_geo_vector operator *(const t_scalar&) const;
    s_geo_vector operator -(void) const;
    s_geo_vector operator /(const t_scalar&) const;

    // length
    t_scalar len(void) const;
    // normalize
    s_geo_vector norm(void) const;

    // input/output
    friend std::ostream& operator<<(std::ostream& os, const s_geo_vector& gv)
    {
    return os <<"<" <<gv._xyz[0] <<"," <<gv._xyz[1] <<"," <<gv._xyz[2] <<">";

    }
    friend std::istream& operator>>(std::istream& is, s_geo_vector& gv)
    {
        return is >>gv._xyz[0] >>gv._xyz[1] >>gv._xyz[2];
    }
};

//******************************************************************************
// GEO_POINT
//******************************************************************************
struct s_geo_point
{
    // friends only to geo structs
    friend struct s_geo_vector;
    friend struct s_geo_ray;
    
    private:
    t_scalar _abc[3];

    public:
    // constructors
    s_geo_point(void);
    s_geo_point(const t_scalar&, const t_scalar&, const t_scalar&);
    s_geo_point(const s_geo_point&);

    // destructor
    ~s_geo_point(void);
    
    // vector operations
    //   - dot product
    t_scalar operator %(const s_geo_vector&) const;
    
    // point operations
    //   - subtraction
    //   - less than
    s_geo_vector operator -(const s_geo_point&) const;
    bool operator <(const s_geo_point&) const;

    // scalar operations
    //   - multiplication
    s_geo_point operator *(const t_scalar&) const;

    // input/output
    friend std::ostream& operator<<(std::ostream& os, const s_geo_point& gp)
    {
        return os <<"[" <<gp._abc[0] <<"," <<gp._abc[1] <<"," <<gp._abc[2] <<"]";
    }
    friend std::istream& operator>>(std::istream& is, s_geo_point& gp)
    {
        return is >>gp._abc[0] >>gp._abc[1] >>gp._abc[2];
    }
};

//******************************************************************************
// GEO_RAY
//******************************************************************************
struct s_geo_ray
{
    // friends only to geo structs
    friend struct s_geo_vector;
    friend struct s_geo_point;

    private:
    s_geo_point _origin;
    s_geo_vector _direction;

    public:
    // constructors
    s_geo_ray(void);
    s_geo_ray(const s_geo_point& gp, const s_geo_vector&);
    
    // destructor
    ~s_geo_ray(void);
    
    // get contents
    s_geo_point get_origin(void) const;
    s_geo_vector get_direction(void) const;

    // ray operations
    //   - addition
    //   - subtraction
    //   - cross product
    s_geo_ray operator +(const s_geo_ray&) const;
    s_geo_ray operator -(const s_geo_ray&) const;
    // cross product
    s_geo_ray operator *(const s_geo_ray&) const;
    s_geo_point pos(const t_scalar&) const;
};

#endif
//// EOF ////
