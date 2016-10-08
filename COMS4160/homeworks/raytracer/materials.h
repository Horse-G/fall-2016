/*
 * Filename:    materials.h
 * Author:      Adam Hadar, anh2130
 * Purpose:     Definitions for materials in a simple raytracer.
 * Edited:      2016-10-08
 */

//************************************************************************
// RGB_TRIPLE
//************************************************************************
struct s_rgb_triple
{
    private:
    t_scalar _r,_g,_b;
    
    public:
    // constructors
    s_rgb_triple(void){}
    s_rgb_triple(const t_scalar& s1, const t_scalar& s2, const t_scalar& s3):
        _r(s1),
        _g(s2),
        _b(s3){}
    s_rgb_triple(const s_rgb_triple& rgb):
        _r(rgb._r),
        _g(rgb._g),
        _b(rgb._b){}
   
    // get contents
    t_scalar get_r(void) const
    {
        return _r;
    }
    t_scalar get_g(void) const
    {
        return _g;
    }
    t_scalar get_b(void) const
    {
        return _b;
    }

    // color operations
    /*  - addition
     *  - subtraction
     *  - multiplication
     *  - increment assignemnt
     */
    s_rgb_triple operator +(const s_rgb_triple& rgb) const
    {
        return s_rgb_triple(_r + rgb._r, _g + rgb._g, _b + rgb._b);
    }
    s_rgb_triple operator -(const s_rgb_triple& rgb) const
    {
        return s_rgb_triple(_r - rgb._r, _g - rgb._g, _b - rgb._b);
    }
    s_rgb_triple operator *(const s_rgb_triple& rgb) const
    {
        return s_rgb_triple(_r * rgb._r, _g * rgb._g, _b * rgb._b);
    }
    s_rgb_triple& operator +=(const s_rgb_triple& rgb)
    {
        _r += rgb._r;
        _g += rgb._g;
        _b += rgb._b;
        return *this;
    }
    // scalar operations
    /*  - multiplication
     */
    s_rgb_triple operator *(const t_scalar& s) const
    {
        return s_rgb_triple(_r * s, _g * s, _b * s);
    }

    // input/output
    friend std::ostream& operator<<(std::ostream& os, const s_rgb_triple& rgb)
    {
        return os <<"`" <<rgb._r <<"," <<rgb._g <<"," <<rgb._b <<"`";
    }
    friend std::istream& operator>>(std::istream& is, s_rgb_triple& rgb)
    {
        return is >>rgb._r >>rgb._g >>rgb._b;
    }
};

//************************************************************************
// MATERIAL
//************************************************************************
struct s_material
{
    private:
    s_rgb_triple _diff, _spec;
    t_scalar _phng;
    s_geo_vector _refl;

    public:
    //constructors
    s_material(void){}
    s_material(s_rgb_triple rgb):
        _diff(rgb),
        _spec(s_rgb_triple(0.0,0.0,0.0)),
        _phng(0.0),
        _refl(s_geo_vector(0.0,0.0,0.0)) {}
    s_material(const s_rgb_triple& rgb1, const s_rgb_triple& rgb2, const t_scalar& s, const s_geo_vector& gv):
        _diff(rgb1),
        _spec(rgb2),
        _phng(s),
        _refl(gv){}

    // get content
    s_rgb_triple get_diff(void) const
    {
        return _diff;
    }
    s_rgb_triple get_spec(void) const
    {
        return _spec;
    }
    t_scalar get_phng(void) const
    {
        return _phng;
    }

    // print
    void print(const char* tab)
    {
        std::cout
            <<tab<<"diffuse "    << _diff <<std::endl
            <<tab<<"specular "   << _spec <<std::endl
            <<tab<<"reflection " << _refl <<std::endl
            <<tab<<"phong "      << _phng <<std::endl;
        return;
    }
};

//// EOF ////
