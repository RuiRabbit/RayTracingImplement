#include "algebra3.h"
#include <vector>

class ColorImage;
class Object;
class Ray;
class Light;

class Camera{
public:
    Camera();
    // w, h, eye, plane[]
    // Camera(int, int, vec3, vec3[]);

    // w, h, eye, vd, vup, fov
    Camera(int, int, vec3, vec3, vec3, float);
    ~Camera() = default;

    Ray getRay(float, float) const;
    ColorImage takePicture(const std::vector<Object*>&,
                           const std::vector<Light*>&) const;

private:
    int w, h;
    vec3 eye;
    // vec3 vd, vu;
    // float fov;
    vec3 topleft;
    vec3 horizontal, vertical;
};