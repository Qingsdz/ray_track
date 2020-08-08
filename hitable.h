#ifndef HITABLE_H
#define HITABLE_H

#include "ray.h"
#include "vec3.h"

class material;
struct hit_record{
    float t;
    vec3 p;
    vec3 normal;
    int type;
    vec3 col;
    float ref;
    material *mat_ptr;

};

class hitable{
public:
    virtual bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const =0;
};

#endif