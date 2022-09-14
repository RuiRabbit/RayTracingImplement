#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "algebra3.h"

using namespace std;

int main(){
    fstream file;
    string filename;
    cin>>filename; cin.ignore();

    file.open(filename, ios::in);

    string str;
    vec3 eye, plane[4];
    int w, h;

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
    }


}