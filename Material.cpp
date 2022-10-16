#include "Material.h"

using namespace std;

Material::Material(vec3 _color,
                   float _ka, float _kd, float _ks,
                   float _exp, float _reflect) : color(_color), 
                                                 ka(_ka), kd(_kd), ks(_ks),
                                                 exp(_exp), reflect(_reflect){}

vec3 Material::getColor() const {
    return color;
}
float Material::getKa() const {
    return ka;
}
float Material::getKd() const {
    return kd;
}
float Material::getKs() const {
    return ks;
}
float Material::getExp() const {
    return exp;
}
float Material::getReflect() const {
    return reflect;
}

vector<Material*> Material::glow = vector<Material*>();

