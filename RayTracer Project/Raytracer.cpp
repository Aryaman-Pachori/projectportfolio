#include "Raytracer.h"
#include "variables.h"
#include <float.h>
using namespace std;

#include <iostream>

Raytracer::Raytracer() {
    // Constructor implementation
}

HitRecord Raytracer::intersectRay(Ray r) {
    double closestDistnace = DBL_MAX;
    HitRecord rec;
    HitRecord closestRec;
    float closest = numeric_limits<float>::infinity();
    bool hit = false;

    for (int i = 0; i<shapes.size();i++) {

         if (shapes[i]->intersect(r, 1e-4, closest, rec)) {

            float distance = glm::distance(r.orig, rec.p);
            // cout << "dist: " << distance << endl;

            // cout << ray.orig.x << " " << ray.orig.y << " " << ray.orig.z << endl;
            // cout << rec.p.x << " " << rec.p.y << " " << rec.p.z << endl;

            // What is light is between object and eye

            if (distance < closestDistnace && distance > 0.001) {
                closestDistnace = distance;
                closestRec.distance = distance;
                // Update hit record
                closestRec = rec;
                closestRec.shapeID = i;
            }
        }
    }

    return closestRec;
}

Color Raytracer::traceRay(HitRecord rec, int& depth) {

    // cout << "Depth: " << depth << endl;
    depth++;

    Color black = Color(0, 0, 0);
    Color color = Color(0, 0, 0);

    // cout << "record.isHit(): " << rec.isHit << endl;
    if (rec.isHit) {
        Geometry* hitShape = shapes[rec.shapeID];
        // cout << "Hit Shape: " << typeid(*hitShape).name() << endl;

        HitRecord shadow;
        Ray shadowray;
        Ray reflectedray;
        vec3 pos = rec.p;
        vec3 normal = rec.normal;

        vec3 lightdir;
        Color tempColor;

        double d;
        double att = 1.0;

        color = color + hitShape->ambient + hitShape->emission;

        for (int i = 0; i < lights.size(); i++) {
            Color lightColor = lights[i]->lightColor;

            if (lights[i]->type == 1) {
                // cout << "Directional Light" << endl;
                lightdir = lights[i]->getPosition();
                att = 1;
            }
            else {
                lightdir = lights[i]->getPosition() - pos;
                d = glm::distance(lights[i]->getPosition(), pos);
                att = attenuation[0] + (attenuation[1] * d) + (attenuation[2] * d * d);
                // cout << "Attenuation: " << att << endl;
            }

            float rayToLight = glm::distance(eyeinit, lights[i]->getPosition());
            // cout << "Ray to Light: " << rayToLight << endl;
            float intersectToLight = glm::distance(pos, lights[i]->getPosition());
            // cout << "Intersect to Intersect: " << intersectToLight << endl;

            // if (eyeToLight < eyeToIntersect) {
            //     return Color(1, 0, 0);
            // }

            lightdir = glm::normalize(lightdir);

            vec3 shadowRayDir = lightdir;
            // vec3 shadowRayPos = pos + 0.2f * normal;
            // vec3 shadowRayPos = pos + 0.2f * normal;
            vec3 shadowRayPos = pos + 0.001f * normal;
            shadowray = Ray(shadowRayPos, shadowRayDir);

            shadow = intersectRay(shadowray);

            // Directional light
            if (lights[i]->type == 1) {
                d = -1;
            }
            else {
                d = glm::distance(shadowray.orig, shadow.p) - 
                    glm::distance(shadowray.orig, lights[i]->getPosition());
                // cout << "d: " << d << endl;
                // cout << "Shadow Distance: " << shadow.distance << endl;
            }
           
            if ((shadow.isHit == false  || d >= 0) || lights[i]->type == 1) {
                vec3 eyeDirection = glm:: normalize(rec.rayPos - pos);
                vec3 halfVector = glm::normalize(lightdir + eyeDirection);

                double nDotL = glm::dot(normal, lightdir);
                double nDotH = glm::dot(normal, halfVector);

                tempColor = hitShape->diffuse * lightColor * std::max(nDotL, 0.0);

                tempColor = tempColor + hitShape->specular * lightColor * pow(std::max(nDotH, 0.0), hitShape->shininess);
                tempColor = tempColor / att;
            }

            color = color + tempColor;
        }

        vec3 reflectRayPos = pos + 0.001f * normal;
        vec3 reflectRayDir = glm::reflect(rec.rayDir, normal);
        // cout << "Reflected Ray Position: " << reflectRayPos.x << " " << reflectRayPos.y << " " << reflectRayPos.z << endl;
        // cout << "Reflected Ray Direction: " << reflectRayDir.x << " " << reflectRayDir.y << " " << reflectRayDir.z << endl;

        rec = intersectRay(Ray(reflectRayPos, reflectRayDir));

        while (depth < 5) {
            color = color + hitShape->specular * traceRay(rec, depth);
        }

        return color;

    } else {
        return black;

    }
}


float Raytracer::clsoestIntersection(Ray ray) {
    // Placeholder for now
    return 0.0;
}
