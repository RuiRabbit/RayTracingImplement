#include "Camera.h"

Camera::Camera(int _w, int _h,
               vec3 _eye, vec3 _plane[]) : w(_w), h(_h), eye(_eye){
    for(int i = 0; i < 4; ++i){
        plane[i] = _plane[i];
    }
}