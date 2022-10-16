#include "algebra3.h"
#include <vector>

class Material{
public:
    Material(vec3, float, float, float, float, float);
    
    vec3 getColor() const;
    float getKa() const;
    float getKd() const;
    float getKs() const;
    float getExp() const;
    float getReflect() const;

    static std::vector<Material*> glow;
    
private:
    vec3 color;
    float ka, kd, ks, exp, reflect;
};