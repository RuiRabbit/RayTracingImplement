#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "algebra3.h"
#include "Object.h"
#include "Camera.h"
#include "PPM.h"
#include "Material.h"

using namespace std;

int main(){
    fstream file;
    string filename;

    cout<<"Please enter input filename: ";
    cin>>filename; cin.ignore();

    file.open(filename, ios::in);
    // white light
    Material::glow.push_back(new Material({1.0, 1.0, 1.0}, 1.0, 0.0, 0.0, 0.0, 0.0));

    string str;
    vec3 eye, vd, vu, plane[4];
    float angle;
    int w, h;
    int cameraMode = 0; // 0 = plane, 1 = vu + angle
    vector<Object*> items;
    vector<Light*> lights;
    vector<Material*> materials;
    while(getline(file, str)){
        stringstream ss(str);
        char choice;
        ss>>choice;

        if(choice == 'E'){
            float x, y, z;
            ss>>x>>y>>z;
            eye = {x, y, z};
        }
        else if(choice == 'V'){
            float x, y, z;
            ss>>x>>y>>z;
            vd = {x, y, z};
            ss>>x>>y>>z;
            vu = {x, y, z};
            cameraMode = 1;
        }
        else if(choice == 'F'){
            ss>>angle;
            cameraMode = 1;
        }
        else if(choice == 'O'){
            for(auto &p : plane){
                float x, y, z;
                ss>>x>>y>>z;
                p = {x, y, z};
            }
        }
        else if(choice == 'R'){
            ss>>w>>h;
        }
        else if(choice == 'S'){
            float x, y, z, r;
            ss>>x>>y>>z>>r;

            items.push_back(new Sphere(materials.back(), {x, y, z}, r));
        }
        else if(choice == 'T'){
            vec3 p[3];
            for(auto &it : p){
                float x, y, z;
                ss>>x>>y>>z;
                it.set(x, y, z);
            }
            items.push_back(new Triangle(materials.back(), p[0], p[1], p[2]));
        }
        else if(choice == 'L'){
            float x, y, z;
            ss>>x>>y>>z;

            // light
            lights.push_back(new Light(Material::glow[0], {x, y, z}));
            items.push_back(lights.back());
        }
        else if(choice == 'M'){
            float r, g, b, ka, kd, ks, exp, reflect;
            ss>>r>>g>>b>>ka>>kd>>ks>>exp>>reflect;

            // material
            materials.push_back(new Material({r, g, b}, ka, kd, ks, exp, reflect));
        }
    }
    // Camera cam;
    // if(cameraMode == 1){
    //     // cam = Camera()
    //     vec3 side = vd ^ vu;
    //     vec3 realVU = side ^ vd;
    //     angle /= 2;
    //     auto rad = atan(tan(angle * acos(-1) / 180) * h / w);
    //     plane[0] = vec3(rotation3Drad(side, rad)
    //                     * (rotation3D(realVU, angle) * vd));
    //     plane[1] = vec3(rotation3Drad(side, rad)
    //                     * (rotation3D(realVU, -angle) * vd));
    //     plane[2] = vec3(rotation3Drad(side, -rad)
    //                     * (rotation3D(realVU, angle) * vd));
    //     plane[3] = vec3(rotation3Drad(side, -rad)
    //                     * (rotation3D(realVU, -angle) * vd));
    // }
    cout<<"Input read successfully"<<endl;
    // cout<<"Item size: "<<items.size()<<endl;
    Camera cam(w, h, eye, vd, vu, angle);
    cout<<"Start tracing"<<endl;
    ColorImage picture = cam.takePicture(items, lights);
    cout<<"Trace complete"<<endl;

    cout<<"Please enter output filename: ";
    cin>>filename; cin.ignore();
    picture.outputPPM(filename.c_str());

    for(auto &obj : items){
        delete obj;
    }
}