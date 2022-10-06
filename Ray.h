#include "algebra3.h"
#include <vector>

class Object;
struct Intersection {
    float t;
    float opacity;
    vec3 color;
    bool operator < (const Intersection& rhs){
        return t < rhs.t;
    }
    bool operator == (const Intersection& rhs){
        return (t == rhs.t && opacity == rhs.opacity && color == rhs.color);
    }
    bool operator != (const Intersection& rhs){
        return !((*this) == rhs);
    }
};


class Ray {
public:
    Ray();
    Ray(vec3, vec3);
    ~Ray() = default;
    
    static const Intersection miss;

    vec3 getOrigin();
    vec3 getDir();

    vec3 trace(const std::vector<Object*>&);

private:
    vec3 origin, dir;
};
