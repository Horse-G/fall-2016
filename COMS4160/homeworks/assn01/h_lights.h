/*
 * Filename:    h_lights.h
 * Author:      Adam Hadar, anh2130
 * Purpose:     Definitions for lights for a simple raytracer.
 * Edited:      2016-10-06
 */

//************************************************************************
// STRUCT LIGHT
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

//// EOF ////
