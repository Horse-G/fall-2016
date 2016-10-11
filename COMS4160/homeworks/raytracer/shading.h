/*
 * Filename:    shading.h
 * Author:      Adam Hadar, anh2130
 * Purpose:     The shading functions for a simple raytracer.
 * Edited:      2016-10-11
 */

//************************************************************************
// SUBROUTINE_SHADING_BLINN_PHONG
//************************************************************************
void shading_blinn_phong(
        s_clr_color&       pixel,
        const s_material&  i_mat,
        const s_intersect& i_sct,
        const s_geo_point& origin,
        const s_clr_color& ambient,
        const std::vector<c_light_point*>& point_lights)
{
    // MEMORY ALLOCATION
    t_uint i;
    t_scalar scale_diff, scale_spec;
    s_geo_vector pl, pv;

    // AMBIENT COMPONENT
    pixel = ambient;
    // POINT LIGHTS
    for(i = 0; i < point_lights.size(); ++i)
    {
        pl = (i_sct.get_point() - point_lights[i]->get_point()).norm();
        pv = (i_sct.get_point() - origin).norm();
        s_geo_vector h = (pv + pl).norm();
        // diffuse component
        scale_diff = i_sct.get_normal() % pl;
        if(scale_diff < 0.0)
            scale_diff = 0.0;
        // specular component
        scale_spec = i_sct.get_normal() % h;
        if(scale_spec < 0.0)
            scale_spec = 0.0;

        pixel += point_lights[i]->get_color() * (i_mat.get_diff()*scale_diff + i_mat.get_spec()*pow(scale_spec, i_mat.get_phng()));
    }
    // DIRECTIONAL LIGHTS
    /*
    for(i = 0; i < directional_lights.size(); ++i)
    {
    }
    */
    return;
}

//************************************************************************
// SUBROUTINE_SHADING_SIMPLE
//************************************************************************
void shading_simple(
        s_clr_color&       pixel,
        const s_material&  i_mat,
        const s_intersect& i_sct,
        const s_geo_point& origin,
        const s_clr_color& ambient,
        const std::vector<c_light_point*> point_lights)
{
    pixel = ambient + i_mat.get_diff();
    return;
}

//// EOF ////
