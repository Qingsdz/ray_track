#include<iostream>
#include<fstream>
#include<limits>
#include"ray.h"
#include"hitable_list.h"
#include"hitable.h"
#include"sphere.h"
#include"tri.h"
using namespace std;

const int nx = 200;
const int ny = 100;

float max_r = 255.99;
float max_g = 255.99;
float max_b = 255.99;

const vec3 lower_left_corner(-2.0, -1.0, -1.0);
const vec3 horizontal(4.0, 0.0, 0.0);
const vec3 vertical(0.0, 2.0, 0.0);
const vec3 origin(0.0, 0.0, 0.0);

const vec3 tri_1(-1.1, 1.3, -1.5);
const vec3 tri_2(1.1, 1.2, -1.5);
const vec3 tri_3(0.1, -0.1, -0.3);

const vec3 tri_4(-1.5, 0.5, -1.5);
const vec3 tri_5(1.5, 0.3, -1.5);
const vec3 tri_6(0.1, -0.1, -0.3);

vec3 color(const ray &r, hitable *world){
    hit_record rec;
    if (world->hit(r, 0.0, (numeric_limits<float>::max)(), rec)) {
        if (rec.type == 0) return 0.5*vec3(rec.normal.x()+1, rec.normal.y()+1, rec.normal.z()+1);
        if (rec.type == 1) return vec3(rec.normal.y()*1, rec.normal.y()*rec.normal.x()*1, rec.normal.x()*1);
    }

    vec3 unit_direction = unit_vector(r.direction());
    float j = 0.5*(unit_direction.y()+1);
    float k = 0.5*(unit_direction.x()+1);
    float l = 0.5*(unit_direction.z()+1);

    return vec3((1-k)*0.1,(1-j)*0.1,(1-l)*0.1)+vec3(k*1, j*0.5, l*1);
} 


int main(){
    ofstream outfile;
    outfile.open("1.ppm", ios::out);
    outfile<<"P3\n"<<nx<<" "<<ny<<"\n255\n";
    hitable *list[4];
    list[0] = new sphere(vec3(0, 0, -1), 0.5);
    list[1] = new sphere(vec3(0,-4,-3), 4);
    list[2] = new triangle(tri_1, tri_2, tri_3);
    list[3] = new triangle(tri_4, tri_5, tri_6);
    hitable *world = new hitable_list(list, 4);

    for(int j = ny-1; j >= 0; j--){
        for(int i = 0; i <= nx-1; i++){
            float u = float(i)/float(nx);
            float v = float(j)/float(ny);
            ray ra(origin, lower_left_corner+ u*horizontal+ v*vertical);
            vec3 col = color(ra, world);


            int r = int(max_r * col[0]);
            int g = int(max_g * col[1]);
            int b = int(max_b * col[2]);
            outfile<<r<<" "<<g<<" "<<b<<" ";
        }
        outfile<<endl;
    }





    outfile.close();
}