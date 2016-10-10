/*
 * Filename:    materials.h
 * Author:      Adam Hadar, anh2130
 * Purpose:     Definitions for materials in a simple raytracer.
 * Edited:      2016-10-09
 */

//************************************************************************
// MATERIAL
//************************************************************************
struct s_material
{
    private:
    s_clr_color _diff, _spec;
    t_scalar _phng;
    s_geo_vector _refl;

    public:
    //constructors
    s_material(void){}
    s_material(s_clr_color cc):
        _diff(cc),
        _spec(s_clr_color(0.0,0.0,0.0)),
        _phng(0.0),
        _refl(s_geo_vector(0.0,0.0,0.0)) {}
    s_material(const s_clr_color& cc1, const s_clr_color& cc2, const t_scalar& s, const s_geo_vector& gv):
        _diff(cc1),
        _spec(cc2),
        _phng(s),
        _refl(gv){}

    // get content
    s_clr_color get_diff(void) const
    {
        return _diff;
    }
    s_clr_color get_spec(void) const
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
            <<tab<<"diffuse    " << _diff <<std::endl
            <<tab<<"specular   " << _spec <<std::endl
            <<tab<<"reflection " << _refl <<std::endl
            <<tab<<"phong      " << _phng <<std::endl;
        return;
    }
};

//// EOF ////
