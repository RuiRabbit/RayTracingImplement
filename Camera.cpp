#include "Camera.h"
#include "Ray.h"
#include "PPM.h"
#include <vector>

using namespace std;

Camera::Camera(int _w, int _h,
               vec3 _eye, vec3 _plane[]) : w(_w), h(_h), eye(_eye){
    for(int i = 0; i < 4; ++i){
        plane[i] = _plane[i];
    }
}

unsigned char colorTransfer(float f){
    return static_cast<unsigned char>((f + 1) / 2.0L * 255.999); 
}

ColorImage Camera::takePicture(const vector<Object*> &items){
    ColorImage ret;
    ret.init(w, h);
    vector<vector<vec3>> v(h + 1, vector<vec3>(w + 1)); 
    for(int i = 0; i <= h; ++i){
        vec3 y1 = (plane[2] - plane[0]) * i / h + plane[0];
        vec3 y2 = (plane[3] - plane[1]) * i / h + plane[1];
        for(int j = 0; j <= w; ++j){
            vec3 dir = (y2 - y1) * j / w + y1 - eye;
            Ray ray(eye, dir);
            v[i][j] = ray.trace(items); 
            // ray.trace(items); 
            // printf("%d %d: (%f, %f, %f)\n", i, j, v[i][j][0], v[i][j][1], v[i][j][2]);
        }
    }
    // printf("Tracing finish\n");
    for(int i = 0; i < h; ++i){
        for(int j = 0; j < w; ++j){
            vec3 color = (v[i][j] + v[i + 1][j]
                        + v[i][j + 1] + v[i + 1][j + 1]) / 4.0L;
            Pixel p = {0, 0, 0};
            p.R = static_cast<unsigned char>(color[0]);
            p.G = static_cast<unsigned char>(color[1]);
            p.B = static_cast<unsigned char>(color[2]);
            // printf("%d %d: (%hd, %hd, %hd)\n", i, j, p.R, p.G, p.B);
            ret.writePixel(j, i, p);
        }
    }
    return ret;
}

