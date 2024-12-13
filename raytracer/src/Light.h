#ifndef LIGHT_H
#define LIGHT_H

#include <glm/glm.hpp>
#include "Color.h"


class Light {
    public:
        Color lightColor;
        int type;

        Light() {
            lightColor = Color(0, 0, 0);
        }

        virtual int getType() {
            return type;
        }

        // virtual float incidentShade(glm::vec3 i, glm::vec3 normal) {
        //     return 0;
        // }

        // virtual bool isBlocked(glm::vec3 input) {
        //     return false;
        // }

        // virtual glm::vec3 calcualteDirection(glm::vec3 pos) {
        //     return glm::vec3(0, 0, 0);
        // }

        virtual glm::vec3 getPosition() {
            return glm::vec3(0, 0, 0);
        }

        // virtual double attenuationColor(glm::vec3 pos) {
        //     return 0;
        // }
};

class DirectionalLight : public Light {
    public:
        glm::vec3 lightPosition;

        DirectionalLight(Color color, glm::vec3 position);
        virtual int getType() override;

        // virtual float incidentShade(glm::vec3 input, glm::vec3 normal) override;
        // virtual bool isBlocked(glm::vec3 input) override;
        // virtual glm::vec3 calcualteDirection(glm::vec3 pos) override;
        virtual glm::vec3 getPosition() override;
        // virtual double attenuationColor(glm::vec3 pos) override;

};

class PointLight : public Light {
    public:
        glm::vec3 lightPosition;
        float* attenuation;

        PointLight(Color color, glm::vec3 position, float* attenuationInput);
        virtual int getType() override;

        // virtual float incidentShade(glm::vec3 input, glm::vec3 normal) override;
        // virtual bool isBlocked(glm::vec3 input) override;
        // virtual glm::vec3 calcualteDirection(glm::vec3 pos) override;
        virtual glm::vec3 getPosition() override;
        // virtual double attenuationColor(glm::vec3 pos) override;
};


#endif // LIGHT_H