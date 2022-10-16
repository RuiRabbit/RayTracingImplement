#include "Object.h"
#include "Ray.h"
#include <algorithm>

Triangle::Triangle(Material *_m, vec3 _p1, vec3 _p2, vec3 _p3)
                    : Object(_m), p1(_p1), p2(_p2), p3(_p3){
    
}

Intersection Triangle::intersect(Ray ray) const {
    /* ------correct------ */
    vec3 s1 = p2 - p1, s2 = p3 - p1;
    vec3 N = s1 ^ s2;

    N.normalize();
    float NdotDir = N * ray.getDir();

    // 正面/背面
    // if(NdotDir < EPSILON)
    //     return Ray::miss;

    float d = (-N) * p1;

    float t = -(N * ray.getOrigin() + d) / NdotDir;
    if(t < 0)
        return Ray::miss;

    vec3 p = ray.getOrigin() + ray.getDir() * t;

    if(N * ((p2 - p1) ^ (p - p1)) < 0.0)
        return Ray::miss;
    if(N * ((p3 - p2) ^ (p - p2)) < 0.0)
        return Ray::miss;
    if(N * ((p1 - p3) ^ (p - p3)) < 0.0)
        return Ray::miss;
    
    Intersection ret;
    ret.t = t;
    ret.obj = (Object*)this;
    return ret;

    // /* ------wrong(uninversable)------ */
    // mat3 A(p2 - p1, p3 - p1, -1 * ray.getDir());
    // A = A.transpose();
    // // printf("inversable\n");
    // vec3 b = ray.getOrigin() - p1;
    // vec3 x = A.inverse() * b;
    // if(x[0] >= 0.0L && x[1] >= 0.0L && x[0] + x[1] <= 1.0L && x[2] > 0.0L){
    // // if(x[0] + x[1] <= 1.0L && x[2] > 0.0L){
    //     Intersection ret;
    //     ret.t = x[2];
    //     ret.opacity = 1.0L;
    //     ret.color = ray.getOrigin() + ret.t * ray.getDir();
    //     ret.color = ((ret.color + 1.0) / 2.0L * 255.999);
    //     printf("cross\n");
    //     return ret;
    // }
    // else{
    //     // printf("out of range: %f %f %f\n", x[0], x[1], x[2]);
    // }
    // return Ray::miss;
}

vec3 Triangle::getNormal(vec3 crossPoint, Ray in) const {
    vec3 N = ((p2 - p1) ^ (p3 - p1)).normalize();
    if(N * in.getDir() > 0.0)
        N *= -1;
    return N;
}