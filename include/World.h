//
// Created by patri on 17/10/2025.
//

#ifndef C___PROGRAM_WORLD_H
#define C___PROGRAM_WORLD_H
#include <vector>
#include "Sphere.h"

class Sphere;

class World
{
    public:
        double deltaTime;
        std::vector<Sphere*> spheres;
        void update();
        void detectCollisions();
        void collision();
        //World();
};

#endif //C___PROGRAM_WORLD_H