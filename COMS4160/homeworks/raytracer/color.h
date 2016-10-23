// Filename:    color.h
// Author:      Adam Hadar, anh2130
// Purpose:     Definitions for materials in a simple raytracer.
// Edited:      2016-10-23

//******************************************************************************
// STRUCT_SPD_RADIANCE
//******************************************************************************
struct s_spd_radiance
{
    private:
    t_scalar _rgb[3];
    
    public:
    // constructors
    s_spd_radiance(void){}
    s_spd_radiance(const t_scalar& s1, const t_scalar& s2, const t_scalar& s3)
    {
        _rgb[0] = s1;
        _rgb[1] = s2;
        _rgb[2] = s3;
    }
    s_spd_radiance(const s_spd_radiance& spdr)
    {
        _rgb[0] = spdr._rgb[0];
        _rgb[1] = spdr._rgb[1];
        _rgb[2] = spdr._rgb[2];
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
    //   - addition
    //   - subtraction
    //   - multiplication
    //   - increment assignemnt
    s_spd_radiance operator +(const s_spd_radiance& spdr) const
    {
        return s_spd_radiance(_rgb[0] + spdr._rgb[0], _rgb[1] + spdr._rgb[1], _rgb[2] + spdr._rgb[2]);
    }
    s_spd_radiance operator -(const s_spd_radiance& spdr) const
    {
        return s_spd_radiance(_rgb[0] - spdr._rgb[0], _rgb[1] - spdr._rgb[1], _rgb[2] - spdr._rgb[2]);
    }
    s_spd_radiance operator *(const s_spd_radiance& spdr) const
    {
        return s_spd_radiance(_rgb[0] * spdr._rgb[0], _rgb[1] * spdr._rgb[1], _rgb[2] * spdr._rgb[2]);
    }
    s_spd_radiance& operator +=(const s_spd_radiance& spdr)
    {
        _rgb[0] += spdr._rgb[0];
        _rgb[1] += spdr._rgb[1];
        _rgb[2] += spdr._rgb[2];
        return *this;
    }
    // scalar operations
    //   - multiplication
    //   - division
    s_spd_radiance operator *(const t_scalar& s) const
    {
        return s_spd_radiance(_rgb[0] * s, _rgb[1] * s, _rgb[2] * s);
    }
    s_spd_radiance operator /(const t_scalar& s) const
    {
        return s_spd_radiance(_rgb[0] / s, _rgb[1] / s, _rgb[2] / s);
    }

    // input/output
    friend std::ostream& operator<<(std::ostream& os, const s_spd_radiance& spdr)
    {
        return os <<"`" <<spdr._rgb[0] <<"," <<spdr._rgb[1] <<"," <<spdr._rgb[2] <<"`";
    }
    friend std::istream& operator>>(std::istream& is, s_spd_radiance& spdr)
    {
        return is >>spdr._rgb[0] >>spdr._rgb[1] >>spdr._rgb[2];
    }
};

//// EOF ////
