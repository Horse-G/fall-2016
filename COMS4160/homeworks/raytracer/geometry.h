/* Filename:    geometry.h
 * Author:      Adam Hadar, anh2130
 * Purpose:     Definitions for vectors, points, and rays for a simple raytracer.
 * Edited:      2016-10-13
 */

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
    s_geo_vector(void){}
    s_geo_vector(const t_scalar& s1, const t_scalar& s2, const t_scalar& s3)
    {
        _xyz[0] = s1;
        _xyz[1] = s2;
        _xyz[2] = s3;
    }
    s_geo_vector(const s_geo_vector& gv)
    {
        _xyz[0] = gv._xyz[0];
        _xyz[1] = gv._xyz[1];
        _xyz[2] = gv._xyz[2];
    }
    
    // destructor
    ~s_geo_vector(void){}

    // get contents
    t_scalar get_x(void) const
    {
        return _xyz[0];
    }
    t_scalar get_z(void) const
    {
        return _xyz[2];
    }

    // vector operations
    /*  - cross product
     *  - dot product
     *  - addition
     *  - subtraction
     */
    s_geo_vector operator *(const s_geo_vector& gv) const
    {
        return s_geo_vector(_xyz[1]*gv._xyz[2] - _xyz[2]*gv._xyz[1], _xyz[2]*gv._xyz[0] - _xyz[0]*gv._xyz[2], _xyz[0]*gv._xyz[1] - _xyz[1]*gv._xyz[0]);
    }
    t_scalar operator %(const s_geo_vector& gv) const
    {
        return _xyz[0]*gv._xyz[0] + _xyz[1]*gv._xyz[1] + _xyz[2]*gv._xyz[2];
    }
    s_geo_vector operator +(const s_geo_vector& gv) const
    {
        return s_geo_vector(_xyz[0]+gv._xyz[0], _xyz[1]+gv._xyz[1], _xyz[2]+gv._xyz[2]);
    }
    s_geo_vector operator -(const s_geo_vector& gv) const
    {
        return s_geo_vector(_xyz[0]-gv._xyz[0], _xyz[1]-gv._xyz[1], _xyz[2]-gv._xyz[2]);
    }

    // scalar operations
    /*  - multiplication
     *  - negation
     *  - division
     */
    s_geo_vector operator *(const t_scalar& s) const
    {
        return s_geo_vector(_xyz[0]*s, _xyz[1]*s, _xyz[2]*s);
    }
    s_geo_vector operator -(void) const
    {
        return s_geo_vector(-_xyz[0],-_xyz[1],-_xyz[2]);
    }
    s_geo_vector operator /(const t_scalar& s) const
    {
        return s_geo_vector(_xyz[0]/s, _xyz[1]/s, _xyz[2]/s);
    }

    // length
    t_scalar len(void) const
    {
        return sqrt(_xyz[0]*_xyz[0] + _xyz[1]*_xyz[1] + _xyz[2]*_xyz[2]);
    }
    // normalize
    s_geo_vector norm(void) const
    {
        t_scalar tmp = sqrt(_xyz[0]*_xyz[0] + _xyz[1]*_xyz[1] + _xyz[2]*_xyz[2]);
        assert(tmp != 0);
        return *this / tmp;
    }

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
    s_geo_point(void){}
    s_geo_point(const t_scalar& s1, const t_scalar& s2, const t_scalar& s3)
    {
        _abc[0] = s1;
        _abc[1] = s2;
        _abc[2] = s3;
    }
    s_geo_point(const s_geo_point& gp)
    {
        _abc[0] = gp._abc[0];
        _abc[1] = gp._abc[1];
        _abc[2] = gp._abc[2];
    }

    // destructor
    ~s_geo_point(void){}
    
    // vector operations
    /*  - dot product
     */
    t_scalar operator %(const s_geo_vector& gv) const
    {
        return _abc[0]*gv._xyz[0] + _abc[1]*gv._xyz[1] + _abc[2]*gv._xyz[2];
    }
    
    // point operations
    /*  - subtraction
     */
    s_geo_vector operator -(const s_geo_point& gp) const
    {
        return s_geo_vector(_abc[0] - gp._abc[0], _abc[1] - gp._abc[1], _abc[2] - gp._abc[2]);
    }

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
        out._abc[0] += _direction._xyz[0] * s;
        out._abc[1] += _direction._xyz[1] * s;
        out._abc[2] += _direction._xyz[2] * s;
        return out;
    }
};

//// EOF ////
