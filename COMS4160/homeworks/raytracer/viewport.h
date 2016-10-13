/* Filename:    viewport.h
 * Author:      Adam Hadar, anh2130
 * Purpose:     Definition of a viewport for a simple raytracer.
 * Edited:      2016-10-13
 */

//******************************************************************************
// VIEWPORT
//******************************************************************************
struct s_viewport
{
    private:
    s_geo_point _eye;
    t_scalar _fl;
    s_geo_vector _uvw[3];
    t_uint _ix, _iy;
    t_scalar _px, _py;

    public:
    // constructors
    s_viewport(void){}
    s_viewport(s_geo_point gp, s_geo_vector gv, t_scalar s1, t_uint u1, t_uint u2, t_scalar s2, t_scalar s3):
        _eye(gp),
        _fl(s1),
        _ix(u1),
        _iy(u2),
        _px(s2),
        _py(s3)
    {
        // TODO fix u if dir too close to `up`
        _uvw[0] =
            (gv.get_x() < EPSILON && -gv.get_x() < EPSILON && gv.get_z() < EPSILON && -gv.get_z() < EPSILON)
            ? s_geo_vector(0.0,0.0,1.0)
            : gv * s_geo_vector(0.0,1.0,0.0);
        _uvw[1] = _uvw[0] * gv;
        _uvw[2] = -gv;
        _uvw[0] = _uvw[0].norm();
        _uvw[1] = _uvw[1].norm();
        _uvw[2] = _uvw[2].norm();
    }

    // destructor
    ~s_viewport(void){}

    // get contents
    s_geo_point get_eye(void) const
    {
        return _eye;
    }
    s_geo_vector get_u(void) const
    {
        return _uvw[0];
    }
    s_geo_vector get_v(void) const
    {
        return _uvw[1];
    }
    s_geo_vector get_w(void) const
    {
        return _uvw[2];
    }
    t_scalar get_fl(void) const
    {
        return _fl;
    }
    t_uint get_ix(void) const
    {
        return _ix;
    }
    t_uint get_iy(void) const
    {
        return _iy;
    }
    t_uint get_px(void) const
    {
        return _px;
    }
    t_uint get_py(void) const
    {
        return _py;
    }
};

//// EOF ////
