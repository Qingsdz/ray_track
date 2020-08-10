#ifndef CAMERA_H
#define CAMERA_H

#include "ray.h"

class camera{
public:
    camera(vec3 look_from, vec3 look_at, vec3 vup, float vfov, float w_h){
        vec3 w = unit_vector(look_from-look_at);
        vec3 u = unit_vector(cross(vup, w));
        vec3 v = unit_vector(cross(w, u));
        float f_height = tan((vfov/360)*M_PI);
        float f_horizontal = f_height*w_h;
        origin = look_from;
        lower_left_corner = look_from-w-f_height*v-f_horizontal*u;
        horizontal = 2*f_horizontal*u;
        vertical = 2*f_height*v;

    }
/*
        lower_left_corner = vec3(-2.0, -1.0, -4);
        horizontal = vec3(4.0, 0.0, 0.0);
        vertical = vec3(0.0, 2.0, 0.0);
        origin = vec3(0.0, 0.0, 4);
*/

    ray get_ray(float s, float t){return ray(origin, lower_left_corner+ s*horizontal+ t*vertical - origin, 1.0);}




    vec3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
    vec3 origin;
};
#endif