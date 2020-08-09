#ifndef SPHERE_H
#define SPHERE_H

#include "hitable.h"
#include "material.h"

class sphere: public hitable{
public:
    sphere(){}
    sphere(vec3 cen, float r, material *m):center(cen), radius(r), ma(m){}

    virtual bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const;

    vec3 center;
    float radius;
    material *ma;
};

bool sphere::hit(const ray &r, float t_min, float t_max, hit_record &rec) const{
//    std::cout<<"---进入撞击球函数---";
    float a = dot(r.direction(),r.direction());
    vec3 oc = r.origin()-center;
    float b = 2*dot(r.direction(), oc);
    float c = dot(oc, oc)-radius*radius;
    float derta = b*b - 4*a*c;
    vec3 mcol(255.99,255.99,255.99);
    vec3 col(0, 0, 0);
    if (derta>0) {
        float temp = (-b-sqrt(derta))/(2*a);
        if (temp > t_min && temp < t_max) {
            rec.t = temp;
            rec.p = r.point_at_parameter(temp);
            rec.normal = (rec.p - center)/radius;
            rec.cross = rec.normal;
            rec.type = 0;
            rec.col = col/mcol;
            rec.mat_ptr = ma;
//            std::cout<<"撞到球前面---"<<std::endl;
            return true;
        }
        temp = (-b+sqrt(derta))/(2*a);
        if (temp > t_min && temp < t_max) {
            rec.t = temp;
            rec.p = r.point_at_parameter(temp);
            rec.normal = (rec.p - center)/radius;
            rec.cross = rec.normal;
            rec.type = 0;
            rec.col = col/mcol;
            rec.mat_ptr = ma;
//            std::cout<<"撞到球后面--"<<std::endl;
            return true;
        }
//        std::cout<<"避免发生多次反射，强制返回---"<<std::endl;
        return 0;
    }
//    std::cout<<"未撞击到球----"<<std::endl;
    return 0;
}
#endif