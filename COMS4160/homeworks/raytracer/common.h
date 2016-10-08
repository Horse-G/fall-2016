/*
 * Filename:    common.h
 * Author:      Adam Hadar, anh2130
 * Purpose:     The main header for a simple raytracer.
 * Edited:      2016-10-08
 */

//************************************************************************
// C_STD_LIBRARIES
//************************************************************************
#include <cstdlib>
#include <cmath>
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
#define FILE_OUT "hw1.exr"
#define EPSILON 1e-7
#define NO_MATERIAL      s_material(s_rgb_triple(0.0,0.0,0.0))
#define DEFAULT_MATERIAL s_material(s_rgb_triple(0.0,0.0,1.0))
#define DEFAULT_AMBIENT s_rgb_triple(0.0,0.0,0.0)
#define OUT_TAB "    "
typedef unsigned int t_uint;
typedef double t_scalar;

//************************************************************************
// CUSTOM_LIBRARIES
//************************************************************************
#include "geometry.h"
#include "intersection.h"
#include "surfaces.h"
#include "materials.h"
#include "lights.h"
#include "viewport.h"
#include "scene.h"
#include "io.h"
#include "shading.h"

//// EOF ////
