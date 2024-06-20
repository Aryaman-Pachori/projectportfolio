#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "ray.h"
#include "Color.h"

// struct Ray
// {
//     glm::vec3 origin;
//     glm::vec3 direction;

//     Ray(const glm::vec3 &orig, const glm::vec3 &dir) : origin(orig), direction(dir) {}
// };

struct HitRecord
{
    float t = 0;          // ray parameter at intersection
    glm::vec3 p = glm::vec3(0, 0, 0);      // point of intersection
    glm::vec3 normal = glm::vec3(0, 0, 0); // normal at the intersection
    glm::vec3 rayPos = glm::vec3(0, 0, 0);
    glm::vec3 rayDir = glm::vec3(0, 0, 0);
    int shapeID;
    bool isHit = false;
    float distance = 0;
};

class Geometry {
    
    public:
        Color ambient;
        Color emission;
        Color diffuse;
        Color specular;
        float shininess;

        Geometry() {}

        virtual bool intersect(Ray &ray, float t_min, float t_max, HitRecord &rec) const = 0;

        Color findColor(HitRecord &rec);

};

class Sphere : public Geometry {
    public:
        glm::vec3 center;
        float radius;
        glm::mat4 transformation;
        glm::mat4 invTransformation;

        Sphere(const glm::vec3 &cen, float r, const glm::mat4 &trans, Color ambient, Color emission, Color diffuse, Color specular, float shininess);

        virtual bool intersect(Ray &ray, float t_min, float t_max, HitRecord &rec) const override;
        // virtual bool intersect(const Ray &ray, float t_min, float t_max, HitRecord &rec) const override;
};

class Triangle : public Geometry {
    public:
        glm::vec3 v0, v1, v2; // vertices of the triangle
        glm::mat4 transformation;
        glm::mat4 invTransformation;

        Triangle(const glm::vec3 &vertex0, const glm::vec3 &vertex1, const glm::vec3 &vertex2, const glm::mat4 &trans, Color ambient, Color emission, Color diffuse, Color specular, float shininess);
        // Triangle(glm::vec3 vertex0, glm::vec3 vertex1, glm::vec3 vertex2, glm::mat4 trans);

        virtual bool intersect(Ray &ray, float t_min, float t_max, HitRecord &rec) const override;
        glm::vec3 normal() const;
};


#endif
