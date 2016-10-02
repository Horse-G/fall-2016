
struct rgb_triple
{
    double r,g,b;
    // constructors
    rgb_triple(){}
    rgb_triple(double _r, double _g, double _b): r(_r), g(_g), b(_b) {}
    rgb_triple(const rgb_triple &c): r(c.r), g(c.g), b(c.b) {}
};

struct Material
{
    rgb_triple diffuse, specular;
    float r;
    geo_vector refl;
    //constructors
    Material(){}
    Material(rgb_triple _diff): diffuse(_diff) {}
    Material(rgb_triple _diff, rgb_triple _spec, float _r, geo_vector _refl):
        diffuse(_diff),
        specular(_spec),
         r(_r),
        refl(_refl) {}

    rgb_triple get_mat()
    {
        return diffuse;
    }
};
