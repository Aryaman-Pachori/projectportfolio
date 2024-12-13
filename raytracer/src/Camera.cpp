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

    fovx = 2 * atan((width * tan((fovy * M_PI /180.0f)/2.0f)) / height);

}

Ray Camera::getRay(float x, float y) {
    vec3 origin = eyeinit;

    double alpha = -tan(fovx / 2.0f) * (y - (width / 2.0f)) / (width / 2.0f);
    double beta = tan((fovy * M_PI / 180.0) / 2.0f) * ((height / 2.0f) - x) / (height / 2.0f);

    vec3 direction = glm::normalize((float)alpha * u + (float)beta * v - w);
    
    return Ray(origin, direction);
}
