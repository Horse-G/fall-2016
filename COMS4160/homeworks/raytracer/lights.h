// Filename:    lights.h
// Author:      Adam Hadar, anh2130
// Purpose:     Definitions for lights for a simple raytracer.
// Edited:      2016-10-23

//******************************************************************************
// VIRTUAL_CLASS_LIGHT
//******************************************************************************
class c_light
{
    protected:
    s_spd_radiance _radiance;
    t_light _type;

    public:
    // subclass destructor
    virtual ~c_light(void) {};
    
    // get contents
    s_spd_radiance get_radiance(void) const
    {
        return _radiance;
    }
    t_light get_type(void) const
    {
        return _type;
    } 
};

//******************************************************************************
// STRUCT_LIGHT_AMBIENT
//******************************************************************************
class c_light_ambient: public c_light
{
    public:
    // constructors
    c_light_ambient(void)
    {
        _type = AMBIENT;
    }
    c_light_ambient(const s_spd_radiance& spdr)
    {
        _radiance = spdr;
        _type = AMBIENT;
    }

    // destructor
    ~c_light_ambient(void){}
};
//******************************************************************************
// CLASS_LIGHT_POINT
//******************************************************************************
class c_light_point: public c_light
{
    private:
    s_geo_point _point;
    t_scalar _intensity;
    
    public:
    // constructors
    c_light_point(void)
    {
        _type = POINT;
    }
    c_light_point(const s_geo_point& gp, const s_spd_radiance& spdr):
        _point(gp)
    {
        _radiance = spdr;
        _type = POINT;
    }
    c_light_point(const s_geo_point& gp, const s_spd_radiance& spdr, const t_scalar& s):
        _point(gp),
        _intensity(s)
    {
        _radiance = spdr;
        _type = POINT;
    }

    // destructor
    ~c_light_point(void){}
    
    // get contents
    s_geo_point get_point(void) const
    {
        return _point;
    }
};

//******************************************************************************
// CLASS_LIGHT_DIRECTIONAL
//******************************************************************************
class c_light_direct: public c_light
{
    private:
    s_geo_vector _direction;

    public:
    // constructors
    c_light_direct(void)
    {
        _type = DIRECTIONAL;
    }
    c_light_direct(const s_geo_vector& gv, const s_spd_radiance& spdr):
        _direction(gv)
    {
        _radiance = spdr;
        _type = DIRECTIONAL;
    }
    
    // destructor
    ~c_light_direct(void){}
    
    // get contents
    s_geo_vector get_direction(void) const
    {
        return _direction;
    }
};

//// EOF ////
