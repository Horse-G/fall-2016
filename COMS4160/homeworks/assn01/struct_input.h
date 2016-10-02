#ifndef STRUCT_INPUT_H
#define STRUCT_INPUT_H

#include "parse.h"
#include <vector>

using namespace std;

class StructInputParser : public Parser
{
    string oStr,mStr,aStr;

    virtual void parse_sphere(geo_point pos, float r);
    //virtual void triangle(geo_point p1, float3 p2, float3 p3);
    //virtual void plane(geo_point n, float d);
    virtual void parse_camera(geo_point pos, geo_vector dir, float d, float iw, float ih, int pw, int ph);
    //virtual void pointLight(float3 pos, float3 rgb);
    //virtual void directionalLight(float3 dir, float3 rgb);
    //virtual void ambientLight(float3 rgb);
    virtual void parse_material(rgb_triple diff, rgb_triple spec, float r, geo_vector refl);

    void finalizeObject();

    public:
    Viewport viewport;
    int cur_material;
    std::vector<Object*>  objects;
    std::vector<Material> materials;
    virtual void parse(const char* name);
};

#endif
