//
// Created by patri on 19/10/2025.
//
#include <cmath>
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

void Engine::initEngine()
{
    camera.zoom = 30.0;
    camera.phi = 1.0;
    camera.theta = 1.0;
    camera.trackingObject = nullptr;
    camera.moveCamera(vector2D<float>(0.0f, 0.0f));

    Sphere *sphere1 = new Sphere();
    Sphere *sphere2 = new Sphere();
    sphere2->position.x = 4;
    sphere1->velocity = vector3D<double>(0, 0, 0);
    sphere2->velocity = vector3D<double>(0, -5, 0);
    sphere1->radius = 2;
    sphere2->radius = 0.5;
    sphere1->mass = 10;

    Sphere *sphere3 = new Sphere();
    sphere3->position.x = -4;
    sphere3->velocity = vector3D<double>(0, 5, 0);

    spheres.push_back(sphere1);
    spheres.push_back(sphere2);
    spheres.push_back(sphere3);
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
    float elasticity = 1.0f;
    vector3D<double> n = (sphere1->position - sphere2->position);
    n = n / norm(n);
    double v = dot((sphere1->velocity - sphere2->velocity), n);
    if (v > 0.0) {return;}
    double J = - (1 + elasticity) / ((1 / sphere1->mass) + (1 / sphere2->mass));
    J = J * v;

    vector3D<double> impulse = J * n;
    sphere1->velocity = sphere1->velocity + impulse / sphere1->mass;
    sphere2->velocity = sphere2->velocity - impulse / sphere2->mass;
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
                std::cout << "Collision detected!" << std::endl;
                separateSpheres(sphere1, sphere2);
                collision(sphere1, sphere2);
            }
        }
    }
}

void Engine::separateSpheres(Sphere *sphere1, Sphere *sphere2)
{
    vector3D<double> differenceVector = sphere1->position - sphere2->position;
    differenceVector = unit(differenceVector) * ((sphere1->radius + sphere2->radius) - norm(differenceVector));
    sphere1->position = sphere1->position + ((1/2.0) * differenceVector);
    sphere2->position = sphere2->position - ((1/2.0) * differenceVector);
}
