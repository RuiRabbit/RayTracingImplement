#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "algebra3.h"
#include "Object.h"
#include "Camera.h"
#include "PPM.h"

using namespace std;

int main(){
    fstream file;
    string filename;
    cout<<"Please enter input filename: ";
    cin>>filename; cin.ignore();

    file.open(filename, ios::in);

    string str;
    vec3 eye, plane[4];
    int w, h;
    vector<Object*> items;
    while(getline(file, str)){
        stringstream ss(str);
        char choice;
        ss>>choice;

        if(choice == 'E'){
            float x, y, z;
            ss>>x>>y>>z;
            eye = {x, y, z};
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

            items.push_back(new Sphere({x, y, z}, r));
        }
        else if(choice == 'T'){
            vec3 p[3];
            for(auto &it : p){
                float x, y, z;
                ss>>x>>y>>z;
                it.set(x, y, z);
            }
            items.push_back(new Triangle(p[0], p[1], p[2]));
        }
    }
    cout<<"Input read successfully"<<endl;
    // cout<<"Item size: "<<items.size()<<endl;
    Camera cam(w, h, eye, plane);
    cout<<"Start tracing"<<endl;
    ColorImage picture = cam.takePicture(items);
    cout<<"Trace complete"<<endl;

    cout<<"Please enter output filename: ";
    cin>>filename; cin.ignore();
    picture.outputPPM(filename.c_str());

    for(auto &obj : items){
        delete obj;
    }
}