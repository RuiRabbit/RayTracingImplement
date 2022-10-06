#include "Object.h"
#include "Ray.h"

Sphere::Sphere(vec3 _origin, float _r) : Object(), origin(_origin), r(_r){

}

Intersection Sphere::intersect(Ray ray) const {
    vec3 oc = ray.getOrigin() - origin;
    vec3 dir = ray.getDir();
    auto a = dir * dir;
    auto b = 2.0L * oc * dir;
    auto c = oc * oc - r * r;
    auto d = b * b - 4.0 * a * c; 
    // printf("miss sphere?\n");
    if(d < 0)
        return Ray::miss;
    // printf("not miss\n");
    Intersection ret;
    ret.t = (-b - sqrt(d)) / (2.0L * a);
    if(ret.t < 0)
        ret.t = (-b + sqrt(d)) / (2.0L * a);
    if(ret.t < 0)
        return Ray::miss;
    ret.opacity = 1.0L;
    ret.color = ray.getOrigin() + ret.t * dir;
    ret.color = ((ret.color + 1.0) / 2.0L * 255.999);
    // printf("intersect with sphere\n");
    return ret;
}