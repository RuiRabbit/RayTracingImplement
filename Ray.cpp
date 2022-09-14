#include "Ray.h"

using namespace std;

Ray::Ray(vec3 _origin, vec3 _dir) : origin(_origin), dir(_dir){

}

const Intersection Ray::miss = {-1, {0, 0, 0}, {0, 0, 0}};

vec3 Ray::trace(const vector<Object*> &items){
    
}