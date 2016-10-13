// Filename:    scene.h
// Author:      Adam Hadar, anh2130
// Purpose:     Definition of a scene for a simple raytracer.
// Edited:      2016-10-13

//******************************************************************************
// SCENE
//******************************************************************************
struct s_scene
{
    private:
    std::vector<s_viewport*>     _viewports;
    std::vector<c_surface*>      _surfaces;
    std::vector<s_material*>     _materials;
    c_light_ambient              _light_ambient;
    std::vector<c_light_point*>  _lights_point;
    std::vector<c_light_direct*> _lights_directional;

    public:
    // constructor
    s_scene(void)
    {
        // pushing back the void, and then the default material
        _materials.push_back(NO_MATERIAL);
        _materials.push_back(DEFAULT_MATERIAL);
        _light_ambient = DEFAULT_AMBIENT;
    }

    // destructor
    ~s_scene(void)
    {
        t_uint i;
        for(i = 0; i < _viewports.size(); i++)
            delete _viewports[i];
        for(i = 0; i < _surfaces.size(); i++)
            delete _surfaces[i];
        for(i = 0; i < _materials.size(); i++)
            delete _materials[i];
        for(i = 0; i < _lights_point.size(); i++)
            delete _lights_point[i];
        for(i = 0; i < _lights_directional.size(); i++)
            delete _lights_directional[i];
    }

    // get contents
    //   These are the only necessary, because the other accessing functions
    //     have friend access;
    t_scalar get_vpx(void) const
    {
        return _viewports[0]->get_px();
    }
    t_scalar get_vpy(void) const
    {
        return _viewports[0]->get_py();
    }

    // This is the only friend function that modifies elements in the scene,
    //   and that is because it fills it up from the scene file.
    friend void io_input_scene(s_scene&, const char*);

    // The rest of the friend functions get passed a const scene, so they will
    //   not modify any elements.
    friend void io_output_scene_verbose(const s_scene&);
    friend void io_output_scene(const s_scene&);
    friend void raytrace_do(Imf::Array2D<Imf::Rgba>&, const t_scalar&, const t_scalar&, const s_scene&);
};

//// EOF ////
