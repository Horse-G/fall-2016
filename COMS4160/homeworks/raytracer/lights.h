// Filename:    lights.h
// Author:      Adam Hadar, anh2130
// Purpose:     Declarations for lights for a simple raytracer.
// Edited:      2016-10-27

#ifndef LIGHTS_H
#define LIGHTS_H

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
    virtual ~c_light(void);
    
    // get contents
    s_spd_radiance get_radiance(void) const;
    t_light get_type(void) const;
};

//******************************************************************************
// STRUCT_LIGHT_AMBIENT
//******************************************************************************
class c_light_ambient: public c_light
{
    public:
    // constructors
    c_light_ambient(void);
    c_light_ambient(const s_spd_radiance&);

    // destructor
    ~c_light_ambient(void);
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
    c_light_point(void);
    c_light_point(const s_geo_point&, const s_spd_radiance&);
    c_light_point(const s_geo_point&, const s_spd_radiance&, const t_scalar&);

    // destructor
    ~c_light_point(void);
    
    // get contents
    s_geo_point get_point(void) const;
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
    c_light_direct(void);
    c_light_direct(const s_geo_vector&, const s_spd_radiance&);
    
    // destructor
    ~c_light_direct(void);
    
    // get contents
    s_geo_vector get_direction(void) const;
};

#endif
//// EOF ////
