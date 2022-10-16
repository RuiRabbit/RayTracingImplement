#include "algebra3.h"

class Ray;
class Material;
struct Intersection;

class Object {
public:
    Object() = default;
    Object(Material *_m) : m(_m) {};
    virtual ~Object() = default;

    virtual Intersection intersect(Ray) const = 0;
    virtual vec3 getNormal(vec3, Ray) const = 0;

    Material* getMaterial() const { return m; };
// public:
protected:
    Material *m = nullptr;
};

class Sphere : public Object {
public:
    Sphere(Material*, vec3, float);
    ~Sphere() = default;

    virtual Intersection intersect(Ray) const override;
    virtual vec3 getNormal(vec3, Ray) const override;
private:
    vec3 origin;
    float r;
};

class Triangle : public Object {
public:
    Triangle(Material*, vec3, vec3, vec3);
    ~Triangle() = default;

    virtual Intersection intersect(Ray) const override;
    virtual vec3 getNormal(vec3, Ray) const override;
private:
    vec3 p1, p2, p3;
};

class Light : public Object {
public:
    Light(Material*, vec3);
    ~Light() = default;

    virtual Intersection intersect(Ray) const override;
    virtual vec3 getNormal(vec3, Ray) const override;

    vec3 getPos() const;
private:
    vec3 p;
};