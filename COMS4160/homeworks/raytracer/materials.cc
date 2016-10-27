// Filename:    materials.cc
// Author:      Adam Hadar, anh2130
// Purpose:     Definitions for materials in a simple raytracer.
// Edited:      2016-10-27

#include "common.h"
#include "color.h"
#include "materials.h"

//************************************************************************
// MATERIAL
//************************************************************************
// subclass destructor
c_material::~c_material(void){}

//************************************************************************
// MATERIAL_DEFAULT
//************************************************************************
// constructors
c_mat_default::c_mat_default(void){}
c_mat_default::c_mat_default(const s_spd_radiance& spdr): _diff(spdr) {}
    
// inherited destructor
c_mat_default::~c_mat_default(void){}

// get contents
s_spd_radiance c_mat_default::get_diff(void) const
{
    return _diff;
}

//************************************************************************
// MATERIAL_BLINN_PHONG
//************************************************************************
// constructors
c_mat_blinn_phong::c_mat_blinn_phong(void){}
c_mat_blinn_phong::c_mat_blinn_phong(const s_spd_radiance& spdr1, const s_spd_radiance& spdr2, const t_scalar& s, const s_spd_radiance& spdr3):
    _diff(spdr1),
    _spec(spdr2),
    _refl(spdr3),
    _phng(s){}

// inherited destructor
c_mat_blinn_phong::~c_mat_blinn_phong(void){}

// get contents
s_spd_radiance c_mat_blinn_phong::get_diff(void) const
{
    return _diff;
}
s_spd_radiance c_mat_blinn_phong::get_spec(void) const
{
    return _spec;
}
t_scalar c_mat_blinn_phong::get_phng(void) const
{
    return _phng;
}
s_spd_radiance c_mat_blinn_phong::get_refl(void) const
{
    return _refl;
}

//************************************************************************
// MATERIAL_CELL_SHADED
//************************************************************************
// constructors
c_mat_cell_shaded::c_mat_cell_shaded(void){}
c_mat_cell_shaded::c_mat_cell_shaded(const s_spd_radiance& spdr): _diff(spdr){}
    
// inherited destructor
c_mat_cell_shaded::~c_mat_cell_shaded(void){}

// get contents
s_spd_radiance c_mat_cell_shaded::get_diff(void) const
{
    return _diff;
}

//// EOF ////
