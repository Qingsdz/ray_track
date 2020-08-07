#ifndef TRI_H
#define TRI_H

#include "hitable.h"
#include "material.h"

class triangle: public hitable{
public:
    triangle(){}
    triangle(vec3 v_0, vec3 v_1, vec3 v_2, material *m):v0(v_0), v1(v_1), v2(v_2), ma(m){}

    virtual bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const;


    vec3 v0;
    vec3 v1;
    vec3 v2;
    material *ma;
};

bool triangle::hit(const ray &r, float t_min, float t_max, hit_record &rec) const {
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
    if (det < 0.0000001) return 0;

    float u = dot(P, T);
    if (u< 0 || u > det) return 0;
    
    vec3 Q = cross(T, E1);
    float v = dot(Q, r.direction());
    if (v < 0 || v+u>det) return 0;
//    if (u < detline) return vec3(-2.0, 0.0, 0.0);
//    if (v < detline) return vec3(-2.0, 0.0, 0.0);
//    else if (v+u > det) return vec3(-2.0, 0.0, 0.0);
    float t = dot(Q, E2);

    float invdet = 1/det;
    t = t*invdet;
    vec3 mcol(255.99,255.99,255.99);
    vec3 col(255,240,255);
    if (t>t_min && t<t_max){
        rec.p = r.point_at_parameter(t);
        rec.t = t;
        vec3 raw_normal = cross(E1, E2);
        rec.normal = vec3(unit_vector(raw_normal));
        rec.col = col/mcol;
        rec.mat_ptr = ma;
        
        return 1;
    }
    return 0;
}    

#endif