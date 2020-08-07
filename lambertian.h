#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H
#include"material.h"

class lambertian : public material{
public:
    lambertian(const vec3 &a): albedo(a){}
    virtual bool scatter(const ray &r_in, const hit_record &rec, vec3 & attenuation,  ray &scattered) const;
    vec3 albedo;    
};

vec3 random_in_unit_sphere(){
        vec3 p;
        do {
            p = 2.0*vec3((rand()%(100)/(float)(100)),
                          (rand()%(100)/(float)(100)),
                          (rand()%(100)/(float)(100)))
                          -vec3(1,1,1);
        } while (p.squared_length() >= 1.0);
        return p;
}

bool lambertian::scatter(const ray &r_in, const hit_record &rec, vec3 & attenuation, ray &scattered) const{
    vec3 H = random_in_unit_sphere();
    scattered = ray(rec.p, rec.normal+H);
    attenuation = albedo;
    return true;
}

#endif






