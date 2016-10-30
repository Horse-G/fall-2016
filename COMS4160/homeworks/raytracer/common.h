// Filename:    common.h
// Author:      Adam Hadar, anh2130
// Purpose:     The main header for a simple raytracer.
// Edited:      2016-10-30

//******************************************************************************
// C_STD_LIBRARIES
//******************************************************************************
#include <cstdlib>
#include <assert.h>
#include <cmath>
#include <limits>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

//******************************************************************************
// OPEN_EXR_LIBRARIES
//******************************************************************************
#include <ImfRgbaFile.h>
#include <ImfStringAttribute.h>
#include <ImfMatrixAttribute.h>
#include <ImfArray.h>

//******************************************************************************
// CONSTANTS_/_TYPES
//******************************************************************************
#define EPSILON      1e-7
#define EP_SHADOW    1e-4
#define EP_REFL      1e-4
typedef unsigned int t_uint;
typedef double       t_scalar;
enum t_surface       {PLANE, TRIANGLE, SPHERE};
enum t_material      {BLINN_PHONG, DEFAULT, CELSHADED};
enum t_light         {AMBIENT, POINT, DIRECTIONAL};
enum t_ray           {PRIMARY, SHADOW, REFLECTION, REFRACTION};

//// EOF ////
