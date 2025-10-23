//
// Created by patri on 19/10/2025.
//

#include "Engine.h"
#include <GL/glew.h>

#include <GL/glut.h>

#include "Globals.h"

Engine::~Engine()
{
    for (Sphere* sphere : spheres)
    {
        delete sphere;
    }
}

void Engine::createSphere()
{
    Sphere *sphere = new Sphere();
    engine->spheres.push_back(sphere);
}

void Engine::update()
{
    calculateDeltaTime();
    calculateFps();

    // is paused still have correct gravity vectors
    if (paused && showGravityVectors)
    {
        for (Sphere* sphere : spheres)
        {
            sphere->calculateNetGravity();
        }
    }

    if (!paused)
    {
        detectCollisions();

        for (Sphere* sphere : spheres)
        {
            sphere->update();
        }
    }
}

void Engine::calculateFps()
{
    frameCount++;

    int currentTime = glutGet(GLUT_ELAPSED_TIME);
    int timeInterval = currentTime - previousTime;

    if (timeInterval > 1000) {
        fps = frameCount / (timeInterval / 1000.0f);
        previousTime = currentTime;
        frameCount = 0;
    }
}

void Engine::collision(Sphere *sphere1, Sphere *sphere2)
{
    // Collision
}

void Engine::calculateDeltaTime()
{
    static int lastTime = 0;
    int currentTime = glutGet(GLUT_ELAPSED_TIME);
    int deltaTime1 = (currentTime - lastTime);
    lastTime = currentTime;
    deltaTime = deltaTime1 * (simulationSpeed / 1000);
}

void Engine::detectCollisions()
{
    for (Sphere* sphere1 : spheres)
    {
        for (Sphere* sphere2 : spheres)
        {
            if (sphere1 == sphere2) {continue;}

            if (sphere1->distanceToSphere(sphere2) < sphere1->radius + sphere2->radius)
            {
                // Collision happened, do physics
                //std::cout << "Collision detected!" << std::endl;
                collision(sphere1, sphere2);
            }
        }
    }
}