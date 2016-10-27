// Filename:    materials.h
// Author:      Adam Hadar, anh2130
// Purpose:     Definitions for materials in a simple raytracer.
// Edited:      2016-10-27

//************************************************************************
// MATERIAL
//************************************************************************
class c_material
{
    public:
    // subclass destructor
    virtual ~c_material(void){}
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
    c_mat_default(void){}
    c_mat_default(const s_spd_radiance& spdr): _diff(spdr) {}
    
    // inherited destructor
    virtual ~c_mat_default(void){}

    // get contents
    s_spd_radiance get_diff(void) const
    {
        return _diff;
    }
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
    c_mat_blinn_phong(void){}
    c_mat_blinn_phong(const s_spd_radiance& spdr1, const s_spd_radiance& spdr2, const t_scalar& s, const s_spd_radiance& spdr3):
        _diff(spdr1),
        _spec(spdr2),
        _refl(spdr3),
        _phng(s){}

    // inherited destructor
    virtual ~c_mat_blinn_phong(void){}

    // get contents
    s_spd_radiance get_diff(void) const
    {
        return _diff;
    }
    s_spd_radiance get_spec(void) const
    {
        return _spec;
    }
    t_scalar get_phng(void) const
    {
        return _phng;
    }
    s_spd_radiance get_refl(void) const
    {
        return _refl;
    }
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
    c_mat_cell_shaded(void){}
    c_mat_cell_shaded(const s_spd_radiance& spdr): _diff(spdr){}
    
    // inherited destructor
    ~c_mat_cell_shaded(void){}

    // get contents
    s_spd_radiance get_diff(void) const
    {
        return _diff;
    }
};

//// EOF ////
