#ifndef RAY_H
#define RAY_H
#include "vec3.h"

class ray{
public:
    ray(){}
    ray(const vec3 &a, const vec3 &b, const float &re) {A = a; B = b; ref_idx = re;}
    vec3 origin() const {return A;}
    vec3 direction() const {return B;}
    vec3 point_at_parameter(float t) const{ return A + t*B;}
    float get_ref_idx() const {return ref_idx;}

    vec3 A;
    vec3 B;
    float ref_idx;


};

#endif