//
// Created by patri on 17/10/2025.
//

#ifndef C___PROGRAM_WORLD_H
#define C___PROGRAM_WORLD_H
#include <vector>
#include "Sphere.h"

class Sphere;

class Engine
{
    public:
        bool paused = true;
        double simulationSpeed = 1.0;
        float gravityStrengthGui = 1.0f;

        double deltaTime = 1;
        std::vector<Sphere*> spheres;

        const double gravityStrength = 100000000000;

        // fps counter variables
        int frameCount = 0;
        int previousTime = 0;
        float fps = 0;

        ~Engine();
        void createSphere();
        void update();
        void detectCollisions();
        void collision(Sphere *sphere1, Sphere *sphere2);

        void calculateFps();
        void calculateDeltaTime();
        //World();
};

#endif //C___PROGRAM_WORLD_H