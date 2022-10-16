#include "algebra3.h"
#include <vector>

class Object;
class Light;
class Material;

struct Intersection {
    float t;
    Object *obj;

    bool operator < (const Intersection& rhs){
        return t < rhs.t;
    }
    bool operator == (const Intersection& rhs){
        return (t == rhs.t && obj == rhs.obj);
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

    vec3 trace(const std::vector<Object*>&, const std::vector<Light*>&, int depth = 0);

private:
    vec3 origin, dir;
};
