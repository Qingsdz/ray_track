#ifndef METAL_H
#define METAL_H
#include "material.h"

class metal:public material{
public:
    metal(const vec3 &a):albedo(a) {}
    virtual bool scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const;
    vec3 albedo;
};

vec3 reflect(const vec3 &v, const vec3 &n){
    return v-2*dot(v,n)*n;
}

bool metal::scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const{
    scattered = ray(rec.p, reflect(unit_vector(r_in.direction()),rec.normal));
    attenuation = albedo;
    return(1);
}

#endif