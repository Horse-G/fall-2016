/*
 * Filename:    lights.h
 * Author:      Adam Hadar, anh2130
 * Purpose:     Definitions for lights for a simple raytracer.
 * Edited:      2016-10-06
 */

//************************************************************************
// STRUCT_LIGHT_AMBIENT
//************************************************************************
struct s_light_ambient
{
    private:
    s_rgb_triple rgb;
    public:
    // constructors
    s_light_ambient(void) {}
    s_light_ambient(s_rgb_triple _rgb): rgb(_rgb) {}
    // get contents
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
// VIRTUAL_CLASS_LIGHT
//************************************************************************
class c_light
{
    protected:
    s_rgb_triple rgb;
    public:
    // subclass destructor
    virtual ~c_light(void) =0;
    // subclass get
    virtual s_rgb_triple get_mat(void) =0;
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
    s_geo_point p;
    t_scalar i;
    public:
    // constructors
    c_light_point(void){}
    c_light_point(s_geo_point _p, s_rgb_triple _rgb):
        p(_p)
        { rgb = _rgb; }
    c_light_point(s_geo_point _p, s_rgb_triple _rgb, t_scalar _i):
        p(_p),
        i(_i)
        { rgb = _rgb; }
    // destructor
    ~c_light_point(void){}
    // get contents
    s_rgb_triple get_mat(void)
    {
        return rgb;
    }
    s_geo_point get_pos(void)
    {
        return p;
    }
    // print
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
    private:
    s_geo_vector v;
    public:
    // constructors
    c_light_direct(void){}
    c_light_direct(s_geo_vector _v, s_rgb_triple _rgb):
        v(_v)
        { rgb = _rgb; }
    // destructor
    ~c_light_direct(void){}
    // get contents
    s_rgb_triple get_mat(void)
    {
        return rgb;
    }
    s_geo_vector get_vec(void)
    {
        return v;
    }
    // print
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
