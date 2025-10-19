//
// Created by patri on 19/10/2025.
//

#include "World.h"

void World::update()
{
    detectCollisions();
    for (Sphere* sphere : spheres)
    {
        sphere->update();
    }
}

void World::detectCollisions()
{
    for (Sphere* sphere1 : spheres)
    {
        for (Sphere* sphere2 : spheres)
        {
            if (sphere1 == sphere2) {continue;}

            if (sphere1->distanceToSphere(sphere2) < sphere1->radius + sphere2->radius)
            {
                // Collision happened, do physics
                std::cout << "Collision detected!" << std::endl;
            }
        }
    }
}