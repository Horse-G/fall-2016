// Filename:    rigging.h
// Author:      Adam Hadar, anh2130
// Purpose:     Declaration of a viewport for a simple raytracer.
// Edited:      2016-11-01

#ifndef RIGGING_H
#define RIGGING_H

//******************************************************************************
// RIGGING
//******************************************************************************
struct s_scene;
struct s_rig_vps
{
    private:
    std::vector<c_viewport*> _list;
    t_uint                   _count, _width, _height;

    public:
    // constructors
    s_rig_vps(void);
    // destructor
    ~s_rig_vps(void);

    void set_dimensions(t_scalar&, t_scalar&);
    void generate_image(Imf::Array2D<Imf::Rgba>&, const s_scene&) const;

    // get contents
    c_viewport* get_vp(const t_uint&) const;
    t_uint get_count(void) const;

    friend void input_scene(s_scene&, s_rig_vps&, const char*);
    friend void output_scene_verbose(const s_scene&, const s_rig_vps&);
    friend void output_scene(const s_scene&, const s_rig_vps&);
};

#endif
//// EOF ////
