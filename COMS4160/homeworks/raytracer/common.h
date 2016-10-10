/*
 * Filename:    common.h
 * Author:      Adam Hadar, anh2130
 * Purpose:     The main header for a simple raytracer.
 * Edited:      2016-10-09
 */

//************************************************************************
// C_STD_LIBRARIES
//************************************************************************
#include <cstdlib>
#include <assert.h>
#include <cmath>
#include <limits>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

//************************************************************************
// OPEN_EXR_LIBRARIES
//************************************************************************
#include <ImfRgbaFile.h>
#include <ImfStringAttribute.h>
#include <ImfMatrixAttribute.h>
#include <ImfArray.h>

//************************************************************************
// CONSTANTS_/_TYPES
//************************************************************************
#define EPSILON          1e-7
#define BLACKNESS        s_intersect(std::numeric_limits<t_scalar>::infinity(),s_geo_point(0.0,0.0,0.0),s_geo_vector(0.0,0.0,0.0),1)
#define NO_MATERIAL      s_material(s_clr_color(0.0,0.0,0.0))
#define DEFAULT_MATERIAL s_material(s_clr_color(0.0,0.0,1.0))
#define DEFAULT_AMBIENT  c_light_ambient(s_clr_color(0.0,0.0,0.0))
#define OUT_TAB          "    "
typedef unsigned int     t_uint;
typedef double           t_scalar;
enum t_surface           {PLANE, TRIANGLE, SPHERE};
enum t_light             {AMBIENT, POINT, DIRECTIONAL};

//************************************************************************
// CUSTOM_LIBRARIES
//************************************************************************
#include "geometry.h"
#include "intersection.h"
#include "surfaces.h"
#include "color.h"
#include "materials.h"
#include "lights.h"
#include "viewport.h"
#include "scene.h"
#include "io.h"
#include "shading.h"

//// EOF ////
