#ifndef CAMERA_H
#define CAMERA_H

#include "ray.h"
#include <glm/vec3.hpp>

using namespace glm;

class Camera {
    private:
        vec3 u;
        vec3 v;
        vec3 w;
        float fovx;

    public:
        Camera();

        // function to compute ray from eye to point s on the viewport
        Ray getRay(float x, float y);


};

#endif
