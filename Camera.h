#include "algebra3.h"

class ColorImage;

class Camera{
public:
    Camera();
    Camera(int, int, vec3, vec3[]);
    ~Camera();

    ColorImage takeShot();

private:
    int w, h;
    vec3 eye;
    vec3 plane[4];
};