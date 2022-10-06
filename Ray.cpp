#include "Ray.h"
#include "Object.h"
#include <algorithm>
#include <iostream>

using namespace std;

Ray::Ray(vec3 _origin, vec3 _dir) : origin(_origin), dir(_dir.normalize()){

}

const Intersection Ray::miss = {-1, 0, {0, 0, 0}};

vec3 Ray::getOrigin(){
    return origin;
}

vec3 Ray::getDir(){
    return dir;
}

vec3 Ray::trace(const vector<Object*> &items){
    vector<Intersection> v;
    for(auto &obj : items){
        Intersection cross = obj->intersect(*this);
        if(cross != Ray::miss){
            v.push_back(cross);
        }
    }
    sort(v.begin(), v.end());
    float op = 1.0L;
    vec3 ret(0.0L, 0.0L, 0.0L);
    for(auto &it : v){
        // cout<<"!"<<endl;
        ret += it.color * it.opacity;
        op *= 1 - it.opacity;
        if(op < EPSILON){
            break;
        }
    }
    return ret;
}