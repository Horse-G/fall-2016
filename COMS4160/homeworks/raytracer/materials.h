// Filename:    materials.h
// Author:      Adam Hadar, anh2130
// Purpose:     Declarations for materials in a simple raytracer.
// Edited:      2016-10-27

#ifndef MATERIALS_H
#define MATERIALS_H

//************************************************************************
// MATERIAL
//************************************************************************
class c_material
{
    public:
    // subclass destructor
    virtual ~c_material(void);
};

//************************************************************************
// MATERIAL_DEFAULT
//************************************************************************
class c_mat_default: public c_material
{
    private:
    s_spd_radiance _diff;
    
    public:
    // constructors
    c_mat_default(void);
    c_mat_default(const s_spd_radiance&);
    
    // inherited destructor
    virtual ~c_mat_default(void);

    // get contents
    s_spd_radiance get_diff(void) const;
};

//************************************************************************
// MATERIAL_BLINN_PHONG
//************************************************************************
class c_mat_blinn_phong: public c_material
{
    private:
    s_spd_radiance _diff, _spec, _refl;
    t_scalar       _phng;
    
    public:
    // constructors
    c_mat_blinn_phong(void);
    c_mat_blinn_phong(const s_spd_radiance&, const s_spd_radiance&, const t_scalar&, const s_spd_radiance&);

    // inherited destructor
    virtual ~c_mat_blinn_phong(void);

    // get contents
    s_spd_radiance get_diff(void) const;
    s_spd_radiance get_spec(void) const;
    t_scalar get_phng(void) const;
    s_spd_radiance get_refl(void) const;
};

//************************************************************************
// MATERIAL_CELL_SHADED
//************************************************************************
class c_mat_cell_shaded: public c_material
{
    private:
    s_spd_radiance _diff;
    
    public:
    // constructors
    c_mat_cell_shaded(void);
    c_mat_cell_shaded(const s_spd_radiance&);
    
    // inherited destructor
    ~c_mat_cell_shaded(void);

    // get contents
    s_spd_radiance get_diff(void) const;
};

#endif
//// EOF ////
