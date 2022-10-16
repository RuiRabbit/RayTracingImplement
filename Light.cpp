#include "Object.h"
#include "Ray.h"

Light::Light(Material* _m, vec3 _p) : Object(_m), p(_p){

}

Intersection Light::intersect(Ray ray) const {
    vec3 origin = ray.getOrigin();
    vec3 dir = ray.getDir();
    vec3 v = p - origin;
    if((dir * v) != dir.length() * v.length())
        return Ray::miss;
    return (Intersection){v.length() / dir.length(), (Object*)this};
}

vec3 Light::getNormal(vec3 crossPoint, Ray in) const {
    return (crossPoint).normalize();
}

vec3 Light::getPos() const {
    return p;
}
