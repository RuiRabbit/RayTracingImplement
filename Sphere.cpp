#include "Object.h"
#include "Ray.h"

Sphere::Sphere(vec3 _origin, float _r) : Object(), origin(_origin), r(_r){

}

Intersection Sphere::intersect(Ray ray) const {
    auto a = 
    return Ray::miss;
}