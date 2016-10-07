/*
 * Filename:    lights.h
 * Author:      Adam Hadar, anh2130
 * Purpose:     Definitions for lights for a simple raytracer.
 * Edited:      2016-10-07
 */

//************************************************************************
// STRUCT_LIGHT_AMBIENT
//************************************************************************
struct s_light_ambient
{
    private:
    s_rgb_triple _rgb;

    public:
    // constructors
    s_light_ambient(void) {}
    s_light_ambient(s_rgb_triple rgb):
        _rgb(rgb){}
    // get contents
    s_rgb_triple get_mat(void) const
    {
        return _rgb;
    }
    void print(const char* tab)
    {
        std::cout
            <<tab <<"ambient_light " <<_rgb <<std::endl;
        return;
    }
};

//************************************************************************
// VIRTUAL_CLASS_LIGHT
//************************************************************************
class c_light
{
    protected:
    s_rgb_triple _rgb;

    public:
    // subclass destructor
    virtual ~c_light(void) =0;
    
    // subclass get
    virtual s_rgb_triple get_color(void) =0;
    
    // subclass print
    virtual void print(const char* tab) =0;
};
c_light::~c_light(void){}

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
    c_light_point(void){}
    c_light_point(const s_geo_point& gp, const s_rgb_triple& rgb):
        _point(gp)
        { _rgb = rgb; }
    c_light_point(const s_geo_point& gp, const s_rgb_triple& rgb, const t_scalar& s):
        _point(gp),
        _intensity(s)
        { _rgb = rgb; }

    // destructor
    ~c_light_point(void){}
    
    // get contents
    s_rgb_triple get_color(void)
    {
        return _rgb;
    }
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
            <<tab <<"color " <<_rgb    <<std::endl;
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
    c_light_direct(void){}
    c_light_direct(const s_geo_vector& gv, const s_rgb_triple& rgb):
        _direction(gv)
        { _rgb = rgb; }
    
    // destructor
    ~c_light_direct(void){}
    
    // get contents
    s_rgb_triple get_color(void)
    {
        return _rgb;
    }
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
            <<tab <<"color "  <<_rgb          <<std::endl;
        return;
    }
};

//// EOF ////
