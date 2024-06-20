#ifndef SCENE_H
#define SCENE_H

#include "Camera.h"
#include "Film.h"
#include "Raytracer.h"

class Scene {
    private:
        Camera* camera;
        Film* film;
        Raytracer* raytracer;

    public:
        Scene();

        void init();

        void renderImage();
        
};

#endif // SCENE_H