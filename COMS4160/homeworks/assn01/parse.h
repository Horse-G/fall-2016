#ifndef PARSE_H
#define PARSE_H

#include <cstdlib>
#include <iostream>
#include "geometry.h"
#include "materials.h"

using namespace std;

inline istream &operator>>(istream &is, geo_point &f) {
    return is>>f.x>>f.y>>f.z;
}
inline istream &operator>>(istream &is, geo_vector &v){
    return is>>v.x>>v.y>>v.z;
}
inline istream &operator>>(istream &is, rgb_triple &c){
    return is>>c.r>>c.g>>c.b;
}
inline ostream &operator<<(ostream &os, geo_point &f) {
    return os<<"<"<<f.x<<","<<f.y<<","<<f.z<<">";
}
inline ostream &operator<<(ostream &os, geo_vector &v){
    return os<<"<"<<v.x<<","<<v.y<<","<<v.z<<">";
}
inline ostream &operator<<(ostream &os, rgb_triple &c){
    return os<<"<"<<c.r<<","<<c.g<<","<<c.b<<">";
}

class Parser
{
protected:
    virtual void parse_sphere(geo_point pos, float r) {}
    //virtual void triangle(geo_point p1, float3 p2, float3 p3) {}
    //virtual void plane(geo_point n, float d) {}
    virtual void parse_camera(geo_point pos, geo_vector dir, float d, float iw, float ih, int pw, int ph) {}
    //virtual void pointLight(geo_point pos, geo_point rgb) {}
    //virtual void directionalLight(geo_point dir, geo_point rgb) {}
    //virtual void ambientLight(geo_point rgb) {}
    virtual void parse_material(rgb_triple diff, rgb_triple spec, float r, rgb_triple refl) {}

public:
    virtual void parse(const char *file);
};

#endif
