#include "algebra3.h"

class Ray;
struct Intersection;

class Object {
public:
    Object() = default;
    ~Object() = default;

    virtual Intersection intersect(Ray) const = 0;

private:
    
};

class Sphere : public Object {
public:
    Sphere(vec3, float);
    ~Sphere() = default;

    virtual Intersection intersect(Ray) const override;
private:
    vec3 origin;
    float r;
};

class Triangle : public Object {
public:
    Triangle(vec3, vec3, vec3);
    ~Triangle() = default;

    virtual Intersection intersect(Ray) const override;
private:
    vec3 origin;
    vec3 s1, s2;
};