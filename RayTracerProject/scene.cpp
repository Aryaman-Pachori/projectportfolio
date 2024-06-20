// This class still needs a lot of work integrating the raytracer.

#include "Scene.h"
#include "variables.h"
#include "ray.h"
#include "Raytracer.h"

#include <iostream>
using namespace std;

Scene::Scene()
{
    // Constructor implementation
}

void Scene::init()
{
    // Initialization implementation
    camera = new Camera();
    film = new Film();
    raytracer = new Raytracer();
}

void Scene::renderImage()
{
    // Render image implementation

    for (int i = 0; i < height; i++)
    {
        float percentage = (i / (float)height) * 100;
        if (percentage == static_cast<int>(percentage))
        {
            cout << "Percentage: " << percentage << "%\n";
        }
        for (int j = 0; j < width; j++)
        {
            // cout << "Ray for " << i << ", " << j << endl;
            // Ray ray = camera->getRay(i, j);
            Ray ray = camera->getRay(i + 0.5, j + 0.5);

            // Need raytrace class that takes in a ray and max depth (later) and output the color
            // Color pixelColor = Color(0, 20, 3); // Replace this line when raytracer class is implemented
            HitRecord rec = raytracer->intersectRay(ray);

            int inputDepth = 0;

            Color pixelColor = raytracer->traceRay(rec, inputDepth);
            if (pixelColor.getR() > 1 || pixelColor.getG() > 1 || pixelColor.getB() > 1)
            {
                // cout << "Color: " << pixelColor.getR() << " " << pixelColor.getG() << " " << pixelColor.getB() << endl;
            }

            if (pixelColor.getR() > 1)
            {
                pixelColor = Color(1, pixelColor.getG(), pixelColor.getB());
            }

            if (pixelColor.getG() > 1)
            {
                pixelColor = Color(pixelColor.getR(), 1, pixelColor.getB());
            }

            if (pixelColor.getB() > 1)
            {
                pixelColor = Color(pixelColor.getR(), pixelColor.getG(), 1);
            }

            // cout << pixelColor.getR() << " " << pixelColor.getG() << " " << pixelColor.getB() << endl;
            // if (i == 0) {
            //     pixelColor = Color(0, 0, 1);
            // }

            // if (j == 0) {
            //     pixelColor = Color(0, 1, 0);
            // }
            // pixelColor = Color(0, 0, 255);

            // Need to give the output color to the film to write to image
            film->addPixelColor(i, j, pixelColor);
        }
    }

    film->saveImage("test.png");
}