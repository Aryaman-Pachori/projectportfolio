#include "Geometry.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Color.h"
#include "variables.h"

#include <iostream>
using namespace std;

// Color Geometry::findColor(HitRecord &rec)
// {
//     if (rec.t <= 0) {
//         return Color(0, 0, 0);
//     }

//     Color tempColor = Color(0, 0, 0);
    
//     for (int i = 0; i < lights.size(); i++) {
//         // cout << !lights[i]->isBlocked(rec.p) << endl;
//         if (!lights[i]->isBlocked(rec.p)) {
//             // cout << rec.p.x << " " << rec.p.y << " " << rec.p.z << endl;
//             // cout << eyeinit.x << " " << eyeinit.y << " " << eyeinit.z << endl;
//             vec3 eyeDirection = glm::normalize(eyeinit - rec.p);
//             // cout << "Eye Direction: " << eyeDirection.x << " " << eyeDirection.y << " " << eyeDirection.z << endl;

//             vec3 lightDirection = lights[i]->calcualteDirection(rec.p);
//             // cout << "Light Direction: " << lightDirection.x << " " << lightDirection.y << " " << lightDirection.z << endl;

//             vec3 half0 = glm::normalize(eyeDirection + lightDirection);

//             Color lambert = diffuse * (lights[i]->incidentShade(rec.p, rec.normal));
//             tempColor = tempColor + lambert;
//             cout << "Lambert: " << lambert.getR() << " " << lambert.getG() << " " << lambert.getB() << endl;

//             float nDotH = glm::dot(rec.normal, half0);

//             Color phong = specular * pow(nDotH, shininess);
//             tempColor = tempColor + phong;
//         }
//     }

//     Color outputColor = tempColor + this->ambient + this->emission;

//     return outputColor;

// }
// Sphere
Sphere::Sphere(const glm::vec3 &cen, float r, const glm::mat4 &trans, Color ambientInput, Color emissionInput, Color diffuseInput, Color specularInput, float shininessInput) {
    this->center = cen;
    this->radius = r;
    this->transformation = trans;
    this->invTransformation = glm::inverse(trans);
    ambient = ambientInput;
    emission = emissionInput;
    diffuse = diffuseInput;
    specular = specularInput;
    shininess = shininessInput;

}

bool Sphere::intersect(Ray &ray, float t_min, float t_max, HitRecord &rec) const
{

    Ray transformedRay = ray.transform(invTransformation);

    glm::vec3 oc = transformedRay.orig - center;

    float a = glm::dot(transformedRay.dir, transformedRay.dir);
    float b = glm::dot(oc, (float)2 * transformedRay.dir);
    float c = glm::dot(oc, oc) - (radius * radius);

    // Aka delta
    float discriminant = b * b - (4 * a * c);

    // No intersection
    if (discriminant < 0) {
        return false;
    }

    // Two roots
    float s1 = (-b + sqrt(discriminant)) / (2 * a);
    float s2 = (-b - sqrt(discriminant)) / (2 * a);

    float t;

    // If both roots are positive
    if (s1 > 0 && s2 > 0) {
        // Find the smaller root
        if (s1 < s2 || s1 == s2) { 
            t = s1; 
        } 
        else { 
            t = s2;
        }
    }
    // If one root is positive
    else if (s1 > 0) { t = s1; }
    else if (s2 > 0) { t = s2; }
    // No positive roots
    else { return false; }
    
    rec.p = vec3(transformation * vec4(transformedRay.orig + t * transformedRay.dir, 1));
    rec.t = t;

    vec3 normal = vec3(invTransformation * vec4(rec.p, 1) - vec4(center, 1));
    normal = vec3(glm::transpose(invTransformation) * vec4(normal, 0));
    normal = glm::normalize(normal);
    rec.normal = normal;
    
    rec.rayPos = ray.orig;
    rec.rayDir = ray.dir;
    rec.isHit = true;
    return true;
    
}

// Triangle
Triangle::Triangle(const glm::vec3 &vertex0, const glm::vec3 &vertex1, const glm::vec3 &vertex2, const glm::mat4 &trans, Color ambientInput, Color emissionInput, Color diffuseInput, Color specularInput, float shininessInput) {
    this->v0 = vertex0;
    this->v1 = vertex1;
    this->v2 = vertex2;
    this->transformation = trans;
    this->invTransformation = glm::inverse(trans);
    ambient = ambientInput;
    emission = emissionInput;
    diffuse = diffuseInput;
    specular = specularInput;
    shininess = shininessInput;
}

bool Triangle::intersect(Ray &ray, float t_min, float t_max, HitRecord &rec) const
{
    glm::vec3 edge1, edge2, h, s, q;
    float a, f, u, v;

    edge1 = v1 - v0;
    edge2 = v2 - v0;
    h = glm::cross(ray.dir, edge2);
    a = glm::dot(edge1, h);
    const float EPSILON = 0.0000001f;

    if (a > -EPSILON && a < EPSILON)
        return false; // ray is parallel to this triangle.

    f = 1.0 / a;
    s = ray.orig - v0;
    u = f * glm::dot(s, h);

    if (u < 0.0 || u > 1.0)
        return false;

    q = glm::cross(s, edge1);
    v = f * glm::dot(ray.dir, q);

    if (v < 0.0 || u + v > 1.0)
        return false;

    float t = f * glm::dot(edge2, q);

    if (t > EPSILON && t < t_max)
    {
        glm::vec3 p = ray.orig + ray.dir * t;
        glm::vec3 v0v1 = v1 - v0;
        glm::vec3 v0v2 = v2 - v0;
        glm::vec3 v0p = p - v0;
        float d00 = glm::dot(v0v1, v0v1);
        float d01 = glm::dot(v0v1, v0v2);
        float d11 = glm::dot(v0v2, v0v2);
        float d20 = glm::dot(v0p, v0v1);
        float d21 = glm::dot(v0p, v0v2);
        float denom = d00 * d11 - d01 * d01;
        float alpha = (d11 * d20 - d01 * d21) / denom;
        float beta = (d00 * d21 - d01 * d20) / denom;
        float gamma = 1.0f - alpha - beta;

        if (alpha >= 0 && beta >= 0 && gamma >= 0)
        { // the intersection is inside the triangle
            rec.t = t;
            rec.p = p;
            rec.normal = this->normal();

            rec.rayPos = ray.orig;
            rec.rayDir = ray.dir;
            rec.isHit = true;
            return true;
        }
    }
    return false;
}

glm::vec3 Triangle::normal() const
{
    return glm::normalize(glm::cross(v1 - v0, v2 - v0));
}
