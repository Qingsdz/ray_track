#include<iostream>
#include<fstream>
#include<limits>
#include"ray.h"
#include"hitable_list.h"
#include"hitable.h"
#include"sphere.h"
#include"tri.h"
#include"camera.h"
#include"material.h"
#include"lambertian.h"
#include"metal.h"
#include"dieletic.h"
using namespace std;

const int nx = 2000;
const int ny = 1000;

const int ns = 50;

float max_r = 255.99;
float max_g = 255.99;
float max_b = 255.99;

const vec3 dir(1, 0, 0);

const vec3 tri_1(-1.1, 0.9, -4);
const vec3 tri_2(1.1, 0.8, -4);
const vec3 tri_3(0, -0.4, -4);

const vec3 tri_4(0.9, 1.1, -2);
const vec3 tri_5(2.3, 1.1, 0);
const vec3 tri_6((tri_4.x()+tri_5.x())/2, -1, -1);


float gen_back(float t){
    if (t>=0 && t<1) return 1;
    else if (t>=1 && t<2) return 0;
    else if (t>=2 && t<3) return 2;
    t = t-3;
    return gen_back(t);
}

vec3 color(const ray &r, hitable *world, int depth){
    hit_record rec;
    if (world->hit(r, 0.01, (numeric_limits<float>::max)(), rec)) {
//        if (rec.type == 0) return 0.5*vec3(rec.normal.x()+1, rec.normal.y()+1, rec.normal.z()+1);
//        if (rec.type == 1) return vec3(rec.normal.y()*1, rec.normal.y()*rec.normal.x()*1, rec.normal.x()*1);
        ray scattered;
        vec3 attenuation;
        if (depth<100 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)){
            return attenuation*color(scattered, world, depth+1);
        }
        else return vec3(0.0, 0.0, 0.0);

    }

    vec3 unit_direction = unit_vector(r.direction());
    float j = 50*(unit_direction.y()+1);
    float k = 50*(unit_direction.x()+1);
    float l = 50*(unit_direction.z()+1);
    float q = gen_back(j);
    float w = gen_back(k);
    if (q == 1.0 && w == 1.0) return vec3(1, 0, 0);
    if (q == 2.0 && w == 2.0) return vec3(0, 1, 0);
    if (q == 0.0 && w == 0.0) return vec3(0, 0, 1);
    else return vec3(1, 1, 1);
//    return 0.7*(vec3((1-k)*0.1,(1-j)*0.1,(1-l)*0.1)+vec3(k*1, j*0.5, l*1))+0.3;
    float t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
} 


int main(){
    ofstream outfile;
    outfile.open("1.ppm", ios::out);
    outfile<<"P3\n"<<nx<<" "<<ny<<"\n255\n";

    hitable *list[5];
    list[0] = new sphere(vec3(0, 0, -1), 0.5, new dielectric(1.5));
    list[1] = new sphere(vec3(0,-100.5,-1), 100, new metal(vec3(0.8, 0.8, 0.0), 0.1));
    list[2] = new triangle(tri_1, tri_2, tri_3, new lambertian(vec3(0.5, 1, 1)));
    list[3] = new triangle(tri_4, tri_5, tri_6, new metal(vec3(0.5, 0.5, 0.5), 0.0));
    list[4] = new sphere(vec3(-1.5, 0, -1), 0.5, new lambertian(vec3(0.8, 0.5, 0.1)));
    hitable *world = new hitable_list(list, 5);

    /*
    hitable *list[4];

    list[0] = new sphere(vec3(0,0,-1), 0.5, new lambertian(vec3(0.1, 0.2, 0.5)));

    list[1] = new sphere(vec3(0,-100.5,-1), 100, new lambertian(vec3(0.8, 0.8, 0.0)));

    list[2] = new sphere(vec3(1,0,-1), 0.5, new metal(vec3(0.8, 0.6, 0.2), 0.0));

    list[3] = new sphere(vec3(-1,0,-1), 0.5, new dielectric(1.5));

    hitable *world = new hitable_list(list,4); */
    camera cam;

    for(int j = ny-1; j >= 0; j--){
        for(int i = 0; i <= nx-1; i++){
            vec3 col(0, 0, 0);
//            cout<<i<<","<<j<<"     ";
            for(int pp = 0; pp<ns; pp++){
                float random = (rand()%(100)/(float)(100));
//            if (i>= 96 && i<=100 && j>=33 && j<=36){
                float u = float(i+random)/float(nx);
                float v = float(j+random)/float(ny);
                ray ra = cam.get_ray(u, v);
                col = color(ra, world, 0)+col;               
            }
            col = col / ns;


            for(int ss = 0; ss<3; ss++){
                if (col[ss]<0.9) col[ss]+0.1;
            }
            int r = int(max_r * col[0]);
            int g = int(max_g * col[1]);
            int b = int(max_b * col[2]);
            outfile<<r<<" "<<g<<" "<<b<<" ";
        }
        outfile<<endl;
//        cout<<endl;
    }





    outfile.close();
}