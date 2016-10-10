/*
 * Filename:    color.h
 * Author:      Adam Hadar, anh2130
 * Purpose:     Definitions for materials in a simple raytracer.
 * Edited:      2016-10-09
 */

//************************************************************************
// STRUCT_CLR_COLOR
//************************************************************************
struct s_clr_color
{
    private:
    t_scalar _rgb[3];
    
    public:
    // constructors
    s_clr_color(void){}
    s_clr_color(const t_scalar& s1, const t_scalar& s2, const t_scalar& s3)
    {
        _rgb[0] = s1;
        _rgb[1] = s2;
        _rgb[2] = s3;
    }
    s_clr_color(const s_clr_color& cc)
    {
        _rgb[0] = cc._rgb[0];
        _rgb[1] = cc._rgb[1];
        _rgb[2] = cc._rgb[2];
    }
   
    // get contents
    t_scalar get_r(void) const
    {
        return _rgb[0];
    }
    t_scalar get_g(void) const
    {
        return _rgb[1];
    }
    t_scalar get_b(void) const
    {
        return _rgb[2];
    }

    // color operations
    /*  - addition
     *  - subtraction
     *  - multiplication
     *  - increment assignemnt
     */
    s_clr_color operator +(const s_clr_color& cc) const
    {
        return s_clr_color(_rgb[0] + cc._rgb[0], _rgb[1] + cc._rgb[1], _rgb[2] + cc._rgb[2]);
    }
    s_clr_color operator -(const s_clr_color& cc) const
    {
        return s_clr_color(_rgb[0] - cc._rgb[0], _rgb[1] - cc._rgb[1], _rgb[2] - cc._rgb[2]);
    }
    s_clr_color operator *(const s_clr_color& cc) const
    {
        return s_clr_color(_rgb[0] * cc._rgb[0], _rgb[1] * cc._rgb[1], _rgb[2] * cc._rgb[2]);
    }
    s_clr_color& operator +=(const s_clr_color& cc)
    {
        _rgb[0] += cc._rgb[0];
        _rgb[1] += cc._rgb[1];
        _rgb[2] += cc._rgb[2];
        return *this;
    }
    // scalar operations
    /*  - multiplication
     */
    s_clr_color operator *(const t_scalar& s) const
    {
        return s_clr_color(_rgb[0] * s, _rgb[1] * s, _rgb[2] * s);
    }

    // input/output
    friend std::ostream& operator<<(std::ostream& os, const s_clr_color& cc)
    {
        return os <<"`" <<cc._rgb[0] <<"," <<cc._rgb[1] <<"," <<cc._rgb[2] <<"`";
    }
    friend std::istream& operator>>(std::istream& is, s_clr_color& cc)
    {
        return is >>cc._rgb[0] >>cc._rgb[1] >>cc._rgb[2];
    }
};

//// EOF ////
