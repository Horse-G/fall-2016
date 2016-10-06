//
// RGB_TRIPLE
//
struct rgb_triple
{
    scalar r,g,b;
    // constructors
    rgb_triple(){}
    rgb_triple(scalar _r, scalar _g, scalar _b): r(_r), g(_g), b(_b) {}
    rgb_triple(const rgb_triple &rgb): r(rgb.r), g(rgb.g), b(rgb.b) {}
    };// i/o
    inline std::ostream& operator<<(std::ostream& os, const rgb_triple& rgb)
    {
        return os<<"`"<<rgb.r<<","<<rgb.g<<","<<rgb.b<<"`";
    }
    inline std::istream& operator>>(std::istream& is, rgb_triple& rgb)
    {
        return is>>rgb.r>>rgb.g>>rgb.b;
    }
// END RGB_TRIPLE

//
// MATERIAL
//
struct Material
{
    rgb_triple diff, spec;
    scalar r;
    geo_vector refl;
    //constructors
    Material(){}
    Material(rgb_triple _diff):
        diff(_diff),
        spec(rgb_triple(0.0,0.0,0.0)),
        r(0.0),
        refl(geo_vector(0.0,0.0,0.0)) {}
    Material(rgb_triple _diff, rgb_triple _spec, scalar _r, geo_vector _refl):
        diff(_diff),
        spec(_spec),
        r(_r),
        refl(_refl) {}

    rgb_triple get_mat()
    {
        return diff;
    }
    };// i/o
    inline std::ostream& operator<<(std::ostream& os, const Material& mat)
    {
        return os<< "    diffuse " << mat.diff <<std::endl
            << "    specular " << mat.spec <<std::endl
            << "    reflection " << mat.refl <<std::endl
            << "    phong " << mat.r  << std::endl;
    }
// END MATERIAL
