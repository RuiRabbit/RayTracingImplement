#include "Ray.h"
#include "Object.h"
#include "Material.h"
#include <algorithm>
#include <iostream>

using namespace std;

Ray::Ray(vec3 _origin, vec3 _dir) : origin(_origin), dir(_dir.normalize()){

}

const Intersection Ray::miss = {-1, nullptr};


vec3 Ray::getOrigin(){
    return origin;
}

vec3 Ray::getDir(){
    return dir;
}

int cnt = 0;

vec3 Ray::trace(const vector<Object*> &items, 
                const std::vector<Light*> &lights,
                int depth){
    vector<Intersection> v;
    if(depth >= 10)
        return {0, 0, 0};
    for(auto &obj : items){
        Intersection cross = obj->intersect(*this);
        if(cross != Ray::miss){
            v.push_back(cross);
        }
    }
    sort(v.begin(), v.end());
    float op = 1.0L;
    vec3 mainColor(0.0L, 0.0L, 0.0L);
    if(v.empty())
        return mainColor;
    auto &cross = v[0];
    if(find(lights.begin(), lights.end(), cross.obj) != lights.end()){
        return cross.obj->getMaterial()->getColor();
    }

    vec3 crossPoint = origin + dir * cross.t;
    vec3 baseColor = cross.obj->getMaterial()->getColor();
    
    vec3 ambient = baseColor * cross.obj->getMaterial()->getKa();
    // can only deal with one light
    for(auto &light : lights){
        // check if in shadow
        bool inShadow = false;
        vec3 toLight = (light->getPos() - crossPoint).normalize();
        Ray ctol(crossPoint, toLight);
        for(auto &obj : items){
            if(obj == cross.obj)
                continue;
            Intersection c = obj->intersect(ctol);
            if(c != Ray::miss && c.t < toLight.length() + EPSILON){
                inShadow = true;
                // cout<<c.t <<" "<< toLight.length()<<"!"<<endl;
            }
        }
        if(inShadow){
            continue;
        }
        else{
            // diffuse
            vec3 N = cross.obj->getNormal(crossPoint, *this);
            vec3 diffuse = {0.0, 0.0, 0.0};
            auto kd = cross.obj->getMaterial()->getKd();
            // tmp = abs(tmp);
            if(kd >= 0.0 && N * toLight > 0.0)
                diffuse += baseColor * (N * toLight) * kd;
            
            // specular
            vec3 specular = {0.0, 0.0, 0.0};
            auto ks = cross.obj->getMaterial()->getKs();
            auto exp = cross.obj->getMaterial()->getExp();
            vec3 H = (toLight + (dir * (-1))).normalize();
            
            if(ks >= 0.0 && N * H > 0.0)
                specular += light->getMaterial()->getColor() * pow((N * H), exp) * ks;
            // specular.print(stdout, "Specular");
            mainColor += diffuse + specular;
            // mainColor += diffuse;
            // cout<<"cross: "<<tmp<<endl;
        }
    }
    if(!lights.empty()){
        mainColor /= lights.size();
    }
    mainColor += ambient;

    auto reflect = cross.obj->getMaterial()->getReflect();

    // Ray next(c)
    // vec3 ret = (1.0L - reflect) * mainColor
    //             + reflect * 

    // mainColor *= 10;
    // mainColor.print(stdout, "RET");
    // cout<<"cnt: "<<cnt<<endl;
    return mainColor;
}