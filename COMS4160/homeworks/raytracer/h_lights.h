/*
 * Filename:    h_lights.h
 * Author:      Adam Hadar, anh2130
 * Purpose:     Definitions for lights for a simple raytracer.
 * Edited:      2016-10-06
 */

//************************************************************************
// STRUCT_LIGHT_AMBIENT
//************************************************************************
struct s_light_ambient
{
    s_rgb_triple rgb;
    s_light_ambient() {}
    s_light_ambient(s_rgb_triple _rgb): rgb(_rgb) {}
    s_rgb_triple get_mat(void)
    {
        return rgb;
    }
    void print(const char* tab)
    {
        std::cout
            <<tab <<"ambient_light " <<rgb <<std::endl;
        return;
    }
};

//************************************************************************
// VIRTUAL_CLASS_LIGHT_POINT
//************************************************************************
class c_light
{
    public:
    s_rgb_triple rgb;
    virtual s_rgb_triple get_mat(void) =0;
    virtual void print(const char* tab) =0;
};

//************************************************************************
// CLASS_LIGHT_POINT
//************************************************************************
class c_light_point: public c_light
{
    public:
    s_geo_point p;
    t_scalar i;

    c_light_point(){}
    c_light_point(s_geo_point _p, s_rgb_triple _rgb):
        p(_p)
        { rgb = _rgb; }
    c_light_point(s_geo_point _p, s_rgb_triple _rgb, t_scalar _i):
        p(_p),
        i(_i)
        { rgb = _rgb; }

    s_rgb_triple get_mat(void)
    {
        return rgb;
    }
    void print(const char* tab)
    {
        std::cout
            <<tab <<"type "  <<"point" <<std::endl
            <<tab <<"point " <<p       <<std::endl
            <<tab <<"color " <<rgb     <<std::endl;
        return;
    }
};

//************************************************************************
// CLASS_LIGHT_DIRECTIONAL
//************************************************************************
class c_light_direct: public c_light
{
    public:
    s_geo_vector v;
    c_light_direct(){}
    c_light_direct(s_geo_vector _v, s_rgb_triple _rgb):
        v(_v)
        { rgb = _rgb; }
    s_rgb_triple get_mat(void)
    {
        return rgb;
    }
    void print(const char* tab)
    {
        std::cout
            <<tab <<"type "   <<"directional" <<std::endl
            <<tab <<"vector " <<v             <<std::endl
            <<tab <<"color "  <<rgb           <<std::endl;
        return;
    }
};

//// EOF ////
