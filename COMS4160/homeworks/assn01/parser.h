#ifndef PARSER_H
#define PARSER_H

#include <cstdlib>
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include <ImfRgbaFile.h>
#include <ImfStringAttribute.h>
#include <ImfMatrixAttribute.h>
#include <ImfArray.h>

#include "h_common.h"

#include "h_geometry.h"
#include "h_surfaces.h"
#include "h_materials.h"

class Parser
{
    public:
    Viewport viewport;
    uint cur_material = 1;
    std::vector<Surface*> surfaces;
    std::vector<Material> materials {Material(rgb_triple(0.0,0.0,1.0))};
    virtual void parse(const char* name);
};

#endif
