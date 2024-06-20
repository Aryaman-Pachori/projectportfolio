#include "Light.h"
#include "ray.h"
#include "variables.h"

#include <glm/glm.hpp>

using namespace glm;
using namespace std;

DirectionalLight::DirectionalLight(Color color, glm::vec3 position)
{
    lightColor = color;
    lightPosition = position;
    type = 1;
}

int DirectionalLight::getType()
{
    return type;
}

// float DirectionalLight::incidentShade(glm::vec3 i, glm::vec3 normal) {
//     return 0;
// }

// bool DirectionalLight::isBlocked(glm::vec3 input) {
//     return false;
// }

// vec3 DirectionalLight::calcualteDirection(glm::vec3 pos) {
//     return -lightPosition;
// }

vec3 DirectionalLight::getPosition()
{
    return lightPosition;
}

// double DirectionalLight::attenuationColor(glm::vec3 pos) {
//     return 0;
// }

PointLight::PointLight(Color color, glm::vec3 position, float *attenuationInput)
{
    lightColor = color;
    lightPosition = position;
    attenuation = attenuationInput;
    type = 0;
}

int PointLight::getType()
{
    return type;
}

// float PointLight::incidentShade(glm::vec3 input, glm::vec3 normal) {

//     vec3 shadowRay = glm::normalize(lightPosition - input);
//     float color = glm::dot(shadowRay, normal);

//     if (color < 0) {
//         return 0;
//     } else {
//         return color;
//     }
// }

// bool PointLight::isBlocked(glm::vec3 input) {
//     vec3 direction = glm::normalize(lightPosition - input);

//     HitRecord hitRecord;
//     float closest = numeric_limits<float>::infinity();
//     Ray r = Ray(input + (float)0.3 * direction, direction);
//     float closestDistance = -1;

//     for (int i = 0; i < shapes.size(); i++) {
//         if (shapes[i]->intersect(r, 1e-4, closest, hitRecord)) {
//             float distance = glm::distance(r.orig, hitRecord.p);
//             if (closestDistance < 0 || distance < closestDistance) {
//                 closestDistance = distance;
//             }
//         }
//     }

//     if (closestDistance < 0) {
//         return false;
//     }

//     float distance2 = glm::length(input - lightPosition);
//     if (closestDistance < distance2) {
//         return true;
//     } else {
//         return false;
//     }
// }

// vec3 PointLight::calcualteDirection(glm::vec3 pos) {
//     return glm::normalize(lightPosition - pos);
// }

vec3 PointLight::getPosition()
{
    return lightPosition;
}

// double PointLight::attenuationColor(glm::vec3 pos) {
//     return 0;
// }
