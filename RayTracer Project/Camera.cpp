//  This class still needs a lot of work on the math calculations.

#include <glm/glm.hpp>
#include "cmath"

#include "Camera.h"
#include "variables.h"

#include <iostream>

using namespace std;

Camera::Camera() {

    w = glm::normalize(eyeinit - center);
    u = -glm::normalize(glm::cross(upinit, w));
    v = glm::cross(w, u);

    std::cout << "fovy: " << fovy << std::endl;

    // float z = tan((fovy * M_PI /180.0f)/2.0f);

    // z = (1/z) * height /2;

    // fovx = 2 * atan((width /2)/z);
    fovx = 2 * atan((width * tan((fovy * M_PI /180.0f)/2.0f)) / height);
    // std::cout << "w: " << w.x << ", " << w.y << ", " << w.z << std::endl;
    // std::cout << "u: " << u.x << ", " << u.y << ", " << u.z << std::endl;
    // std::cout << "v: " << v.x << ", " << v.y << ", " << v.z << std::endl;
    // std::cout << "fovy: " << fovy * M_PI /180.0 << std::endl;
    // std::cout << "fovx: " << fovx << std::endl;
}

Ray Camera::getRay(float x, float y) {
    vec3 origin = eyeinit;

    // cout << "fovx " << fovx << endl;
    // cout << "fovy " << (fovy * M_PI /180.0) << endl;

    // cout << "pixel.getY(): " << y << endl;
    // cout << "width: " << width << endl;
    
    // double x_range = -tan((fovy * M_PI / 180.0) / 2.0f) * width / height;
    // double alpha = x_range * (y - (width / 2.0f)) / (width / 2.0f);

    // cout << "x: " << x << " y: " << y << endl;

    double alpha = -tan(fovx / 2.0f) * (y - (width / 2.0f)) / (width / 2.0f);
    double beta = tan((fovy * M_PI / 180.0) / 2.0f) * ((height / 2.0f) - x) / (height / 2.0f);
    // cout << "alpha: " << alpha << " beta: " << beta << endl;
    
    vec3 direction = glm::normalize((float)alpha * u + (float)beta * v - w);
    // cout << "Ray direction: " << direction.x << " " << direction.y << " " << direction.z << endl;
    return Ray(origin, direction);
}
