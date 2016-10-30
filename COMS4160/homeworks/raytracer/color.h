// Filename:    color.h
// Author:      Adam Hadar, anh2130
// Purpose:     Declarations for color in a simple raytracer.
// Edited:      2016-10-30

#ifndef COLOR_H
#define COLOR_H

//******************************************************************************
// STRUCT_SPD_RADIANCE
//******************************************************************************
struct s_spd_radiance
{
    private:
    t_scalar _rgb[3];
    
    public:
    // constructors
    s_spd_radiance(void);
    s_spd_radiance(const t_scalar&, const t_scalar&, const t_scalar&);
    s_spd_radiance(const s_spd_radiance&);
   
    // get contents
    t_scalar get_r(void) const;
    t_scalar get_g(void) const;
    t_scalar get_b(void) const;

    // color operations
    //   - addition
    //   - subtraction
    //   - multiplication
    //   - increment assignemnt
    s_spd_radiance operator +(const s_spd_radiance&) const;
    s_spd_radiance operator -(const s_spd_radiance&) const;
    s_spd_radiance operator *(const s_spd_radiance&) const;
    s_spd_radiance& operator +=(const s_spd_radiance&);

    // scalar operations
    //   - multiplication
    //   - division
    //   - greater than
    s_spd_radiance operator *(const t_scalar&) const;
    s_spd_radiance operator /(const t_scalar&) const;
    bool operator >(const t_scalar&) const;
    s_spd_radiance& operator /=(const t_scalar&);

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

#endif
//// EOF ////
