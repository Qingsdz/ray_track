#ifndef TRI_H
#define TRI_H

#include "hitable.h"
#include "material.h"

class triangle: public hitable{
public:
    triangle(){}
    triangle(vec3 v_0, vec3 v_1, vec3 v_2, vec3 cen, material *m):v0(v_0), v1(v_1), v2(v_2), center(cen), ma(m){}

    virtual bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const;


    vec3 v0;
    vec3 v1;
    vec3 v2;
    vec3 center;
    material *ma;
};

bool triangle::hit(const ray &r, float t_min, float t_max, hit_record &rec) const {
//    std::cout<<"---进入撞击三角面函数";
    vec3 E1 = v1 - v0;
    vec3 E2 = v2 - v0;

    vec3 P = cross(r.direction(),E2);
    float det = dot(P, E1);
    
    vec3 T;
    if (det>0)  T = r.origin() - v0;
    else {
        T = v0 - r.origin();
        det = -det;
    }
    if (det < 0.0000001) {
 //       std::cout<<"未撞击到三角形----"<<std::endl;
        return 0;}

    float u = dot(P, T);
    if (u< 0 || u > det) {
//        std::cout<<"未撞击到三角形----"<<std::endl;
        return 0;}
    
    vec3 Q = cross(T, E1);
    float v = dot(Q, r.direction());
    if (v < 0 || v+u>det) {
//        std::cout<<"未撞击到三角形----"<<std::endl;
        return 0;}
//    if (u < detline) return vec3(-2.0, 0.0, 0.0);
//    if (v < detline) return vec3(-2.0, 0.0, 0.0);
//    else if (v+u > det) return vec3(-2.0, 0.0, 0.0);
    float t = dot(Q, E2);

    float invdet = 1/det;
    t = t*invdet;
//    vec3 mcol(255.99,255.99,255.99);
//    vec3 col(255,240,255);
    if (t>t_min && t<t_max){
        rec.p = r.point_at_parameter(t);
        rec.t = t;
        vec3 raw_normal = cross(E1, E2);
        vec3 nor_center = (v0+v1+v2)/3;
        rec.normal = vec3(unit_vector(nor_center - center));
        rec.cross = cross(E1, E2);
        rec.col = vec3(u*invdet, v*invdet, t);
        rec.mat_ptr = ma;
        rec.type = 1;
//        std::cout<<"撞击到三角形----"<<std::endl;
        return 1;
    }
//    std::cout<<"未撞击到三角形----"<<std::endl;
    return 0;
}    

#endif