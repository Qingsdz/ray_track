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

const int nx = 200;
const int ny = 200;

const int ns = 10;

float max_r = 255.99;
float max_g = 255.99;
float max_b = 255.99;

float dir = 0.4;


const vec3 tri_1(-1.2+dir, 0, -2);
const vec3 tri_2(1.2+dir, 0, -2);
const vec3 tri_3(0.1+dir, 0.9, -2);
const vec3 tri_7(0.5+dir, -0.3, -1.3);
const vec3 center((tri_1+tri_2+tri_3+tri_7)/4);
/*
const vec3 tri_1(-1.1, 1.3, -2);
const vec3 tri_2(1.1, 1.2, -2);
const vec3 tri_3(0, -0.1, -2);
*/
const vec3 tri_8(-1.1, 0.9, -5);
const vec3 tri_9(1.1, 0.8, -5);
const vec3 tri_10(0, -0.3, -5);


const vec3 tri_4(1.1+dir, 1.1, -4);
const vec3 tri_5(2.2+dir, 0.8, -0.5);
const vec3 tri_6((tri_4.x()+tri_5.x())/2+0.1, -1, -2.4);
const vec3 tri_11((tri_4.x()+tri_5.x())/2+0.1+1.1, -1-0.3, -2.4+3.5);

const vec3 tri_bak_1(-3.1,-3.1,3.1);
const vec3 tri_bak_2(-3.1,-3.1,-3.1);
const vec3 tri_bak_4(3.1,-3.1,3.1);
const vec3 tri_bak_3(3.1,-3.1,-3.1);
const vec3 tri_bak_11(-3.1,3.1,3.1);
const vec3 tri_bak_22(-3.1,3.1,-3.1);
const vec3 tri_bak_44(3.1,3.1,3.1);
const vec3 tri_bak_33(3.1,3.1,-3.1);





float gen_back_b(float t){
    if (t>=0 && t<1) return 1;
    else if (t>=1 && t<2) return 0;
    else if (t>=2 && t<3) return 2;
    t = t-3;
    return gen_back(t);
}


void debug3(const vec3 &a){
    cout<<a.x()<<" "<<a.y()<<" "<<a.z()<<"    ";
}

vec3 color(const ray &r, hitable *world, int depth){
    hit_record rec;
//    cout<<"--进入着色函数--"<<endl;
    if (world->hit(r, 0.001, (numeric_limits<float>::max)(), rec)) {
//        if (rec.type == 0) return 0.5*vec3(rec.normal.x()+1, rec.normal.y()+1, rec.normal.z()+1);
//        if (rec.type == 1) return vec3(rec.normal.y()*1, rec.normal.y()*rec.normal.x()*1, rec.normal.x()*1);
        ray scattered;
        vec3 attenuation;
        int state = rec.mat_ptr->scatter(r, rec, attenuation, scattered);
        if (depth<60 && state){
//            vec3 debug = attenuation*color(scattered, world, depth+1);
//            cout<<debug.x()<<"     ";
            return attenuation*color(scattered, world, depth+1);
        }
        else if(depth<50 && state == 0) return attenuation;
        else {
//            std::cout<<"flase"<<std::endl;
            return vec3(0.0, 0.0, 0.0);
        }

    }


//    cout<<"---返回背景rgb----"<<endl;
    vec3 unit_direction = unit_vector(r.direction());
    float j = 50*(unit_direction.y()+1);
    float k = 50*(unit_direction.x()+1);
//    float l = 50*(unit_direction.z()+1);
    float q = gen_back_b(j);
    float w = gen_back_b(k);
    if (q == 1.0 && w == 1.0) return vec3(1, 0, 0);
    if (q == 2.0 && w == 2.0) return vec3(0, 1, 0);
    if (q == 0.0 && w == 0.0) return vec3(0, 0, 1);
    else return vec3(0,0,0);
//    return 0.7*(vec3((1-k)*0.1,(1-j)*0.1,(1-l)*0.1)+vec3(k*1, j*0.5, l*1))+0.3;
    float t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
} 


int main(){
    ofstream outfile;
    outfile.open("1.ppm", ios::out);
    outfile<<"P3\n"<<nx<<" "<<ny<<"\n255\n";
//    cout<<"begin";
    int i = 0;
    hitable *list[20];
    list[0] = new sphere(vec3(-0.8, 0, -0.1), 0.3, new dielectric(1.5));
//    list[1] = new sphere(vec3(0,-100.5,-1), 100, new metal(vec3(0.8, 0.8, 0.0), 0.05));
    list[1] = new triangle(tri_1, tri_2, tri_3, center, new dielectric(1.2));
    list[2] = new triangle(tri_1, tri_2, tri_7, center, new dielectric(1.2));
    list[3] = new triangle(tri_1, tri_3, tri_7, center, new dielectric(1.2));
    list[4] = new triangle(tri_4, tri_5, tri_6, (tri_4+tri_5+tri_6)/3, new metal(vec3(0.8, 0.8, 0.8), 0.0));
    list[5] = new sphere(vec3(-1.5, 0, -1), 0.5, new lambertian(vec3(0.8, 0.5, 0.1),0));
    list[6] = new triangle(tri_11, tri_5, tri_6, (tri_11+tri_5+tri_6)/3, new metal(vec3(0.8, 0.8, 0.8), 0.0));
//    list[7] = new sphere(vec3(0,0,0), 6, new lambertian(vec3(1, 1, 1),1));
/*
    vec3 ew(52,93,167);
    vec3 wewe(255,255,255);
    list[11] = new triangle(tri_bak_1, tri_bak_2, tri_bak_11, vec3(-11,-11,-11), new lambertian(ew/wewe,0));
    list[12] = new triangle(tri_bak_11, tri_bak_22, tri_bak_2, vec3(-11,-11,-11), new lambertian(ew/wewe,0)); //左

    list[9] = new triangle(tri_bak_44, tri_bak_33, tri_bak_3, vec3(-11,-11,-11), new lambertian(vec3(1,0,1),0));
    list[10] = new triangle(tri_bak_44, tri_bak_4, tri_bak_3, vec3(-11,-11,-11), new lambertian(vec3(1,0,1),0)); //右


    list[7] = new triangle(tri_bak_33, tri_bak_22, tri_bak_2, vec3(-11,-11,-11), new lambertian(vec3(1,1,1),0));
    list[8] = new triangle(tri_bak_2, tri_bak_3, tri_bak_33, vec3(-11,-11,-11), new lambertian(vec3(1,1,1),0));

    list[13] = new triangle(tri_bak_44, tri_bak_11, tri_bak_4, vec3(-11,-11,-11), new lambertian(vec3(1,0,0),0));
    list[14] = new triangle(tri_bak_11, tri_bak_4, tri_bak_1, vec3(-11,-11,-11), new lambertian(vec3(1,0,0),0));
 
    list[15] = new sphere(vec3(0,2,0), 0.5, new lambertian(vec3(1,1,1),1));

    list[16] = new triangle(tri_bak_44, tri_bak_33, tri_bak_11, vec3(-11,-11,-11), new lambertian(vec3(1,1,1),0));
    list[17] = new triangle(tri_bak_11, tri_bak_33, tri_bak_22, vec3(-11,-11,-11), new lambertian(vec3(1,1,1),0));

    list[18] = new triangle(tri_bak_1, tri_bak_4, tri_bak_3, vec3(-11,-11,-11), new lambertian(vec3(1,0,1),0));
    list[19] = new triangle(tri_bak_1, tri_bak_2, tri_bak_3, vec3(-11,-11,-11), new lambertian(vec3(1,0,1),0));
*/
    hitable *world = new hitable_list(list,20);

    /*
    hitable *list[4];

    list[0] = new sphere(vec3(0,0,-1), 0.5, new lambertian(vec3(0.1, 0.2, 0.5)));

    list[1] = new sphere(vec3(0,-100.5,-1), 100, new lambertian(vec3(0.8, 0.8, 0.0)));

    list[2] = new sphere(vec3(1,0,-1), 0.5, new metal(vec3(0.8, 0.6, 0.2), 0.0));

    list[3] = new sphere(vec3(-1,0,-1), 0.5, new dielectric(1.5));

    hitable *world = new hitable_list(list,4); */
    camera cam(vec3(0,0,2), vec3(0,0,-2),vec3(0,1,0), 85, float(nx)/float(ny));
//    cout<<"----初始化完成-----"<<endl;
    for(int j = ny-1; j >= 0; j--){
        for(int i = 0; i <= nx-1; i++){
            vec3 col(0, 0, 0);
//            cout<<"#-#-#-#-#-开始进入第 "<<i<<" "<<j<<" 层循环-#-#-#-#-#"<<endl;
//            cout<<i<<","<<j<<"     ";
            for(int pp = 0; pp<ns; pp++){
                float random = (rand()%(100)/(float)(100));
//            if (i>= 64 && i<=66 && j>=26 && j<=28){
                float u = float(i+random)/float(nx);
                float v = float(j+random)/float(ny);
                ray ra = cam.get_ray(u, v);
//                cout<<"---得到光线向量-----"<<endl;
//                debug3(ra.origin());
//                debug3(ra.direction());
//                cout<<endl;
                col = color(ra, world, 0)+col;
//                cout << i << " "<< j <<" ";          
            }

            col = col / ns;


//            for(int ss = 0; ss<3; ss++){
//                if (col[ss]<0.9) col[ss]+0.1;
//            }
            int r = int(max_r * col[0]);
            int g = int(max_g * col[1]);
            int b = int(max_b * col[2]);
            outfile<<r<<" "<<g<<" "<<b<<" ";
        }
        outfile<<endl;
        std::cout<<j<<endl;
//        cout<<endl;
    }
    outfile.close();
}