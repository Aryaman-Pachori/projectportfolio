#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "Color.h"
#include "ray.h"
#include "Geometry.h"

class Raytracer
{
public:
    Raytracer();

    HitRecord intersectRay(Ray r);

    Color traceRay(HitRecord rec, int &depth);

    float clsoestIntersection(Ray ray);
};

#endif // RAYTRACER_H