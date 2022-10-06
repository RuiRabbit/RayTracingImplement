#include "algebra3.h"
#include <vector>

class ColorImage;
class Object;

class Camera{
public:
    Camera();
    // w, h, eye, plane[]
    Camera(int, int, vec3, vec3[]);
    ~Camera() = default;

    ColorImage takePicture(const std::vector<Object*>&);

private:
    int w, h;
    vec3 eye;
    vec3 plane[4];
};