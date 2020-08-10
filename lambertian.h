#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H
#include"material.h"

class lambertian : public material{
public:
    lambertian(const vec3 &a, int b): albedo(a),back(b){}
    virtual int scatter(const ray &r_in, const hit_record &rec, vec3 & attenuation,  ray &scattered) const;
    vec3 albedo;
    int back;    
};

vec3 random_in_unit_sphere(){
        vec3 p;
        do {
            p = 2.0*vec3((rand()%(100)/(float)(100)),
                          (rand()%(100)/(float)(100)),
                          (rand()%(100)/(float)(100)))
                          -vec3(1,1,1);
        } while (p.squared_length() >= 1.0||p.y()<0.6);
        return p;
}

float gen_back(float t){
    if (t>=0 && t<1) return 1;
    else if (t>=1 && t<2) return 0;
    else if (t>=2 && t<3) return 2;
    t = t-3;
    return gen_back(t);
}


int lambertian::scatter(const ray &r_in, const hit_record &rec, vec3 & attenuation, ray &scattered) const{
    vec3 H = random_in_unit_sphere();
    scattered = ray(rec.p, rec.cross+H, r_in.get_ref_idx());
    vec3 unit_direction;
    if(back == 1){
        attenuation = vec3(albedo.x()*rec.col.y(),1,1);
        return 0;
    }
    else if (rec.type == 0){
        unit_direction = rec.normal;
        float j = 0.5*(unit_direction.y()+1);
        float k = 0.5*(unit_direction.x()+1);
        float l = 0.5*(unit_direction.z()+1);
        attenuation = vec3((1-k)*0.1,(1-j)*0.1,(1-l)*0.1)+vec3(k*1, j*0.5, l*1);
        /*
        float j = 25*(unit_direction.y()+1);
        float k = 25*(unit_direction.x()+1);
        float q = gen_back(j);
        float w = gen_back(k);
        if (q == 1.0 && w == 1.0) attenuation = vec3(1, 0, 0);
        if (q == 2.0 && w == 2.0) attenuation = vec3(0, 1, 0);
        if (q == 0.0 && w == 0.0) attenuation = vec3(0, 0, 1);
        else attenuation = vec3(1, 1, 1);
        */
    }
    else if (rec.type == 1){
        /*
        float j = 50*rec.col.x();
        float k = 50*rec.col.y();
        j = gen_back(j);
        k = gen_back(k);
        if ((j+k)==1) attenuation = albedo;
        else attenuation = vec3(1,1,1);
        */
       attenuation = albedo;
    }


    return 1;
}

#endif






