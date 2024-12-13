#ifndef RAY_H
#define RAY_H

#include <glm/glm.hpp>
using namespace glm;

class Ray {
    public:

    vec3 orig;
    vec3 dir;

    Ray() {}

    Ray (const vec3& origin, const vec3& direction) {
        this->orig = origin;
        this->dir = direction;
    }

    vec3 origin() const { return orig; }
    vec3 direction() const { return dir; }

    vec3 at(float t) const {
        return orig + (t * dir);
    }

    Ray transform(const mat4 transMatrix) {
        vec3 transformedOrig = vec3(transMatrix * vec4(orig, 1.0));
        vec3 transformedDir = normalize(vec3(transMatrix * vec4(dir, 0.0)));

        return Ray(transformedOrig, transformedDir);
    }
};

#endif