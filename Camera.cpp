#include "Camera.h"
#include "Ray.h"
#include "PPM.h"
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

// Camera::Camera(int _w, int _h,
//                vec3 _eye, vec3 _plane[]) : w(_w), h(_h), eye(_eye){
//     for(int i = 0; i < 4; ++i){
//         plane[i] = _plane[i];
//     }
// }

Camera::Camera(int _w, int _h, vec3 _eye, vec3 _vd, vec3 _vu, float _fov)
               : w(_w), h(_h), eye(_eye){
    
    auto vd = _vd.normalize();
    auto u = (vd ^ _vu).normalize();
    auto v = (u ^ vd).normalize();
    
    auto theta = _fov * acos(-1) / 180;
    // cout<<theta<<endl;
    auto halfWidth = tan(theta / 2);
    auto width = 2.0L * halfWidth;
    auto height = width * h / w;

    horizontal = width * u;
    vertical = height * v * (-1);
    topleft = eye + vd - horizontal / 2 - vertical / 2;
}

unsigned char colorTransfer(float f){
    int val = f * 255.999;
    if(val < 0)
        val = 0;
    if(val > 255)
        val = 255;
    return static_cast<unsigned char>(val); 
}

Ray Camera::getRay(float s, float t) const {
    return Ray(eye, topleft + s * horizontal + t * vertical - eye);
}

ColorImage Camera::takePicture(const vector<Object*> &items,
                               const vector<Light*> &lights) const {
    ColorImage ret;
    ret.init(w, h);
    vector<vector<vec3>> v(h + 1, vector<vec3>(w + 1)); 
    // std::cout<<w<<" "<<h<<endl;
    for(int i = 0; i <= h; ++i){
        // vec3 y1 = (plane[2] - plane[0]) * i / h + plane[0];
        // vec3 y2 = (plane[3] - plane[1]) * i / h + plane[1];
        for(int j = 0; j <= w; ++j){
            // vec3 dir = (y2 - y1) * j / w + y1 - eye;
            Ray ray = getRay((double)j / w, (double)i / h);
            v[i][j] = ray.trace(items, lights); 
            // ray.trace(items); 
            // printf("%d %d: (%f, %f, %f)\n", i, j, v[i][j][0], v[i][j][1], v[i][j][2]);
            // fflush(stdout);
        }
    }
    // printf("Tracing finish\n");
    for(int i = 0; i < h; ++i){
        for(int j = 0; j < w; ++j){
            vec3 color = (v[i][j] + v[i + 1][j]
                        + v[i][j + 1] + v[i + 1][j + 1]) / 4.0L;
            Pixel p = {0, 0, 0};
            p.R = static_cast<unsigned char>(colorTransfer(color[0]));
            p.G = static_cast<unsigned char>(colorTransfer(color[1]));
            p.B = static_cast<unsigned char>(colorTransfer(color[2]));
            // printf("%d %d: (%hd, %hd, %hd)\n", i, j, p.R, p.G, p.B);
            ret.writePixel(j, i, p);
        }
    }
    return ret;
}

