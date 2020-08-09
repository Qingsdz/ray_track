#ifndef METAL_H
#define METAL_H
#include "material.h"
#include "lambertian.h"

class metal:public material{
public:
    metal(const vec3 &a, float f):albedo(a) { if(f<1) fuzz = f; else fuzz = 1;}
    virtual bool scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const;
    vec3 albedo;
    float fuzz;
};

vec3 reflect(const vec3 &v, const vec3 &n){
    return v-2*dot(v,n)*n;
}

bool metal::scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const{
    scattered = ray(rec.p, reflect(unit_vector(r_in.direction()),rec.cross)+fuzz*random_in_unit_sphere(), r_in.get_ref_idx());
    attenuation = albedo;
    return(1);
}

#endif