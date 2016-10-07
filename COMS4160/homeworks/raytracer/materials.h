/*
 * Filename:    materials.h
 * Author:      Adam Hadar, anh2130
 * Purpose:     Definitions for materials in a simple raytracer.
 * Edited:      2016-10-06
 */

//************************************************************************
// RGB_TRIPLE
//************************************************************************
struct s_rgb_triple
{
    t_scalar r,g,b;
    // constructors
    s_rgb_triple(){}
    s_rgb_triple(t_scalar _r, t_scalar _g, t_scalar _b): r(_r), g(_g), b(_b) {}
    s_rgb_triple(const s_rgb_triple &rgb): r(rgb.r), g(rgb.g), b(rgb.b) {}
};
inline std::ostream& operator<<(std::ostream& os, const s_rgb_triple& rgb)
{
    return os <<"`" <<rgb.r <<"," <<rgb.g <<"," <<rgb.b <<"`";
}
inline std::istream& operator>>(std::istream& is, s_rgb_triple& rgb)
{
    return is >>rgb.r >>rgb.g >>rgb.b;
}

//************************************************************************
// MATERIAL
//************************************************************************
struct s_material
{
    s_rgb_triple diff, spec;
    t_scalar r;
    s_geo_vector refl;
    //constructors
    s_material(){}
    s_material(s_rgb_triple _diff):
        diff(_diff),
        spec(s_rgb_triple(0.0,0.0,0.0)),
        r(0.0),
        refl(s_geo_vector(0.0,0.0,0.0)) {}
    s_material(s_rgb_triple _diff, s_rgb_triple _spec, t_scalar _r, s_geo_vector _refl):
        diff(_diff),
        spec(_spec),
        r(_r),
        refl(_refl) {}

    s_rgb_triple get_mat()
    {
        return diff;
    }
    void print(const char* tab)
    {
        std::cout
            <<tab<<"diffuse "    << diff <<std::endl
            <<tab<<"specular "   << spec <<std::endl
            <<tab<<"reflection " << refl <<std::endl
            <<tab<<"phong "      << r    <<std::endl;
        return;
    }
};

//// EOF ////
