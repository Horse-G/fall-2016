// Filename:    scene.h
// Author:      Adam Hadar, anh2130
// Purpose:     Declaration of a scene for a simple raytracer.
// Edited:      2016-10-30

#ifndef SCENE_H
#define SCENE_H

//******************************************************************************
// SCENE
//******************************************************************************
struct s_scene
{
    private:
    std::vector<c_surface*>         _surfaces;
    std::vector<c_mat_blinn_phong*> _materials;
    c_light_ambient                 _light_ambient;
    std::vector<c_light_point*>     _lights_point;
    std::vector<c_light_direct*>    _lights_directional;

    public:
    // constructor
    s_scene(void);

    // destructor
    ~s_scene(void);

    // This is the only friend function that modifies elements in the scene,
    //   and that is because it fills it up from the scene file.
    friend void input_scene(s_scene&, std::vector<s_viewport*>&, const char*);

    // The rest of the friend functions get passed a const scene, so they will
    //   not modify any elements.
    friend void output_scene_verbose(const s_scene&, const std::vector<s_viewport*>&);
    friend void output_scene(const s_scene&, const std::vector<s_viewport*>&);
    friend s_spd_radiance compute_L(const s_geo_ray&, const s_scene&, const t_uint&, const t_scalar&, const t_scalar&, const t_ray&, const c_light_point&);
    friend void raytrace_do(Imf::Array2D<Imf::Rgba>&, const t_scalar&, const t_scalar&, const t_scalar&, const t_scalar&, const s_scene&, const s_viewport&);
};

#endif
//// EOF ////
