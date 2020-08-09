#ifndef HITABLE_LIST_H
#define HITABLE_LIST_H
#include <limits>  
#include "hitable.h"

class hitable_list: public hitable{
public:
    hitable_list(){}
    hitable_list(hitable **l, int n) {list = l; list_size = n;}

    virtual bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const;
    hitable **list;
    int list_size;
};


bool hitable_list::hit(const ray &r, float t_min, float t_max, hit_record &rec) const{
//    std::cout<<"--进入判断撞击最近距离函数--";
    hit_record temp_rec;
    bool hit_anything = 0;
    float closest_so_far = t_max;
    for (int i = 0; i<list_size; i++){
        if (list[i]->hit(r, t_min, closest_so_far, temp_rec)){
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
 //       std::cout<<"是否撞击到 list"<<i<<" "<<hit_anything<<std::endl;
    }

    return hit_anything;
}

#endif