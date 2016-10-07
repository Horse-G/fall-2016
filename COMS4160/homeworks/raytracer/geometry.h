/*
 * Filename:    geometry.h
 * Author:      Adam Hadar, anh2130
 * Purpose:     Definitions for vectors, points, and rays for a simple raytracer.
 * Edited:      2016-10-07
 */

//************************************************************************
// GEO_VECTOR
//************************************************************************
struct s_geo_vector
{
    // friends only to geo structs
    friend struct s_geo_point;
    friend struct s_geo_ray;
    
    private:
    t_scalar _x,_y,_z;
    
    public:
    // constructors
    s_geo_vector(void){}
    s_geo_vector(const t_scalar& s1, const t_scalar& s2, const t_scalar& s3):
        _x(s1),
        _y(s2),
        _z(s3){}
    s_geo_vector(const s_geo_vector& gv):
        _x(gv._x),
        _y(gv._y),
        _z(gv._z){}
    
    // destructor
    ~s_geo_vector(void){}

    // vector operations
    /*  - cross product
     *  - dot product
     *  - addition
     *  - subtraction
     */
    s_geo_vector operator *(const s_geo_vector& gv) const
    {
        return s_geo_vector(_y*gv._z - _z*gv._y, _z*gv._x - _x*gv._z, _x*gv._y - _y*gv._x);
    }
    t_scalar operator %(const s_geo_vector& gv) const
    {
        return _x*gv._x + _y*gv._y + _z*gv._z;
    }
    s_geo_vector operator +(const s_geo_vector& gv) const
    {
        return s_geo_vector(_x+gv._x, _y+gv._y, _z+gv._z);
    }
    s_geo_vector operator -(const s_geo_vector& gv) const
    {
        return s_geo_vector(_x-gv._x, _y-gv._y, _z-gv._z);
    }

    // scalar operations
    /*  - multiplication
     *  - negation
     *  - division
     */
    s_geo_vector operator *(const t_scalar& s) const
    {
        return s_geo_vector(_x*s, _y*s, _z*s);
    }
    s_geo_vector operator -(void) const
    {
        return s_geo_vector(-_x,-_y,-_z);
    }
    s_geo_vector operator /(const t_scalar& s) const
    {
        return s_geo_vector(_x/s, _y/s, _z/s);
    }

    // normalize
    s_geo_vector norm(void) const
    {
        return *this / sqrt(_x*_x + _y*_y + _z*_z);
    }

    // input/output
    friend std::ostream& operator<<(std::ostream& os, const s_geo_vector& gv)
    {
    return os <<"<" <<gv._x <<"," <<gv._y <<"," <<gv._z <<">";

    }
    friend std::istream& operator>>(std::istream& is, s_geo_vector& gv)
    {
        return is >>gv._x >>gv._y >>gv._z;
    }
};

//************************************************************************
// GEO_POINT
//************************************************************************
struct s_geo_point
{
    // friends only to geo structs
    friend struct s_geo_vector;
    friend struct s_geo_ray;
    
    private:
    t_scalar _x,_y,_z;

    public:
    // constructors
    s_geo_point(void){}
    s_geo_point(const t_scalar& s1, const t_scalar& s2, const t_scalar& s3):
        _x(s1),
        _y(s2),
        _z(s3){}
    s_geo_point(const s_geo_point& gp):
        _x(gp._x),
        _y(gp._y),
        _z(gp._z){}

    // destructor
    ~s_geo_point(void){}
    
    // vector operations
    /*  - dot product
     */
    t_scalar operator %(const s_geo_vector& gv) const
    {
        return _x*gv._x + _y*gv._y + _z*gv._z;
    }
    
    // point operations
    /*  - subtraction
     */
    s_geo_vector operator -(const s_geo_point& gp) const
    {
        return s_geo_vector(_x - gp._x, _y - gp._y, _z - gp._z);
    }

    // input/output
    friend std::ostream& operator<<(std::ostream& os, const s_geo_point& gp)
    {
        return os <<"[" <<gp._x <<"," <<gp._y <<"," <<gp._z <<"]";
    }
    friend std::istream& operator>>(std::istream& is, s_geo_point& gp)
    {
        return is >>gp._x >>gp._y >>gp._z;
    }
};

//************************************************************************
// GEO_RAY
//************************************************************************
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
    s_geo_ray(void){}
    s_geo_ray(const s_geo_point& gp, const s_geo_vector& gv):
        _origin(gp),
        _direction(gv.norm()){}
    
    // destructor
    ~s_geo_ray(void){}
    
    // get contents
    s_geo_point get_origin(void) const
    {
        return _origin;
    }
    s_geo_vector get_direction(void) const
    {
        return _direction;
    }

    // ray operations
    /*  - addition
     *  - subtraction
     *  - cross product
     */
    s_geo_ray operator +(const s_geo_ray& gr) const
    {
        return s_geo_ray(_origin, _direction + gr._direction);
    }
    s_geo_ray operator -(const s_geo_ray& gr) const
    {
        return s_geo_ray(_origin, _direction - gr._direction);
    }
    // cross product
    s_geo_ray operator *(const s_geo_ray& gr) const
    {
        return s_geo_ray(_origin, _direction * gr._direction);
    }
    s_geo_point pos(t_scalar s) const
    {
        s_geo_point out = _origin;
        out._x += _direction._x * s;
        out._y += _direction._y * s;
        out._z += _direction._z * s;
        return out;
    }

    // output
    friend std::ostream& operator<<(std::ostream& os, const s_geo_ray& gr)
    {
        return os
            <<"Ray"                     <<std::endl
            <<"origin " <<gr._origin    <<std::endl
            <<"direct " <<gr._direction <<std::endl;
    }
};

//// EOF ////
