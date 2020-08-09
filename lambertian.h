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
    scattered = ray(rec.p, rec.cross+H, r_in.get_ref_idx());
    vec3 unit_direction;
    if (rec.type == 0){
        unit_direction = rec.normal;
        float j = 0.5*(unit_direction.y()+1);
        float k = 0.5*(unit_direction.x()+1);
        float l = 0.5*(unit_direction.z()+1);
        attenuation = vec3((1-k)*0.1,(1-j)*0.1,(1-l)*0.1)+vec3(k*1, j*0.5, l*1);
    }
    else if (rec.type == 1){
        float j = rec.col.x();
        attenuation = vec3(1*j, 0.5, 0.1);
    }


    return true;
}

#endif






