/*
 * Filename:    viewport.h
 * Author:      Adam Hadar, anh2130
 * Purpose:     Definition of a viewport for a simple raytracer.
 * Edited:      2016-10-07
 */

//************************************************************************
// VIEWPORT
//************************************************************************
struct s_viewport
{
    s_geo_point eye;
    t_scalar fl;
    s_geo_vector u, v, w;
    t_uint ix, iy;
    t_scalar px, py;

    s_viewport(void){}
    s_viewport(s_geo_point _eye, s_geo_vector dir, t_scalar _fl, t_uint _ix, t_uint _iy, t_scalar _px, t_scalar _py):
        eye(_eye),
        fl(_fl),
        ix(_ix),
        iy(_iy),
        px(_px),
        py(_py)
    {
        // TODO fix u if dir too close to `up`
        u = dir * s_geo_vector(0.0,1.0,0.0);
        v = u * dir;
        w = -dir;
        u = u.norm();
        v = v.norm();
        w = w.norm();
    }
    void print(const char* tab)
    {
        std::cout
            <<tab <<"eye "   <<eye         <<std::endl
            <<tab <<"u "     <<u           <<std::endl
            <<tab <<"v "     <<v           <<std::endl
            <<tab <<"w "     <<w           <<std::endl
            <<tab <<"fl "    <<fl          <<std::endl
            <<tab <<"ix,iy " <<ix<<","<<iy <<std::endl
            <<tab <<"px,py " <<px<<","<<iy <<std::endl;
        return;
    }
};

//// EOF ////
