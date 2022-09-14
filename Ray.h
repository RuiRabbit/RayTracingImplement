#include "algebra3.h"
#include <vector>

class Object;
struct Intersection {
    float t;
    vec3 opacity;
    vec3 color;
    bool operator < (const Intersection& rhs){
        return t < rhs.t;
    }
};


class Ray {
public:
    Ray();
    Ray(vec3, vec3);
    ~Ray();

    vec3 getOrigin();
    vec3 getDir();

    vec3 trace(const std::vector<Object*>&);
    static const Intersection miss;

private:
    vec3 origin, dir;
};
