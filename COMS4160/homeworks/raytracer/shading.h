/*
 * Filename:    shading.h
 * Author:      Adam Hadar, anh2130
 * Purpose:     The shading functions for a simple raytracer.
 * Edited:      2016-10-08
 */

//************************************************************************
// SUBROUTINE_SHADING_BLINN_PHONG
//************************************************************************
void shading_blinn_phong(
        s_rgb_triple& pixel,
        const s_rgb_triple& comp_diff,
        const s_rgb_triple& comp_spec,
        const s_intersect& i_sct,
        const s_geo_point& origin,
        const s_rgb_triple& ambient,
        const std::vector<c_light_point*>& point_lights)
{
    t_uint i;
    t_scalar scale;
    s_geo_vector pl, pv;

    pixel = ambient;
    // point lights
    for(i = 0; i < point_lights.size(); ++i)
    {
        pl = (i_sct.get_point() - point_lights[i]->get_point()).norm();
        pv = (i_sct.get_point() - origin).norm();
         
        // diffuse component
        scale = i_sct.get_normal() % pl;
        if(scale < 0.0)
            scale = 0.0;
        pixel += comp_diff * point_lights[i]->get_color() * scale;
        
        // specular component
        s_geo_vector h = (pv + pl).norm();
        scale = i_sct.get_normal() % h;
        if(scale < 0.0)
            scale = 0.0;
        pixel += comp_spec * point_lights[i]->get_color() * scale;
    }
    return;
}

//// EOF ////
