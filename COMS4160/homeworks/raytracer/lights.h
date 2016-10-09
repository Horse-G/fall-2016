/*
 * Filename:    lights.h
 * Author:      Adam Hadar, anh2130
 * Purpose:     Definitions for lights for a simple raytracer.
 * Edited:      2016-10-09
 */

//************************************************************************
// VIRTUAL_CLASS_LIGHT
//************************************************************************
class c_light
{
    protected:
    s_clr_color _color;
    t_light _type;

    public:
    // subclass destructor
    virtual ~c_light(void) {};
    
    // get contents
    s_clr_color get_color(void) const
    {
        return _color;
    }
    t_light get_type(void) const
    {
        return _type;
    } 
    // subclass print
    virtual void print(const char* tab) =0;
};

//************************************************************************
// STRUCT_LIGHT_AMBIENT
//************************************************************************
class c_light_ambient: public c_light
{
    public:
    // constructors
    c_light_ambient(void)
    {
        _type = AMBIENT;
    }
    c_light_ambient(const s_clr_color& cc)
    {
        _color = cc;
        _type = AMBIENT;
    }

    // destructor
    ~c_light_ambient(void){}

    // print
    void print(const char* tab)
    {
        std::cout
            <<tab <<"ambient_light " <<_color <<std::endl;
        return;
    }
};
//************************************************************************
// CLASS_LIGHT_POINT
//************************************************************************
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
    c_light_point(const s_geo_point& gp, const s_clr_color& cc):
        _point(gp)
    {
        _color = cc;
        _type = POINT;
    }
    c_light_point(const s_geo_point& gp, const s_clr_color& cc, const t_scalar& s):
        _point(gp),
        _intensity(s)
    {
        _color = cc;
        _type = POINT;
    }

    // destructor
    ~c_light_point(void){}
    
    // get contents
    s_geo_point get_point(void) const
    {
        return _point;
    }
    // print
    void print(const char* tab)
    {
        std::cout
            <<tab <<"type "  <<"point" <<std::endl
            <<tab <<"point " <<_point  <<std::endl
            <<tab <<"color " <<_color  <<std::endl;
        return;
    }
};

//************************************************************************
// CLASS_LIGHT_DIRECTIONAL
//************************************************************************
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
    c_light_direct(const s_geo_vector& gv, const s_clr_color& cc):
        _direction(gv)
    {
        _color = cc;
        _type = DIRECTIONAL;
    }
    
    // destructor
    ~c_light_direct(void){}
    
    // get contents
    s_geo_vector get_direction(void) const
    {
        return _direction;
    }
    // print
    void print(const char* tab)
    {
        std::cout
            <<tab <<"type "   <<"directional" <<std::endl
            <<tab <<"vector " <<_direction    <<std::endl
            <<tab <<"color "  <<_color        <<std::endl;
        return;
    }
};

//// EOF ////
