//
// Created by patri on 17/10/2025.
//

#include "Sphere.h"
#include "Engine.h"
#include "Globals.h"
#include <cstdlib>
#include <GL/freeglut_std.h>


Sphere::~Sphere()
{
    for (TrailSphere* sphere : trailSpheres)
    {
        delete sphere;
    }
}


void Sphere::update()
{
    applyGravity();
    updateVelocity();
    updatePosition();

    int currentTime = glutGet(GLUT_ELAPSED_TIME);

    // More trail spheres are created when a sphere is moving faster
    if (showTrails && currentTime % std::max((int)(80 / std::max(norm2(velocity), 1.0)), 1) == 0)
    {
        createTrailSphere();
    }

    if (showTrails)
    {
        for (TrailSphere *trail : trailSpheres)
        {
            trail->update();
        }
    }
}

void Sphere::updatePosition()
{
    position += velocity * engine->deltaTime;
}

void Sphere::updateVelocity()
{
    velocity += acceleration * engine->deltaTime;
}



void Sphere::applyGravity()
{
    vector3D<double> sumOfGravityVector = calculateNetGravity();
    vector3D<double> gravityAcceleration = sumOfGravityVector / mass;
    acceleration = gravityAcceleration * engine->gravityStrength;
}

// Method for calculating direction and strength of net gravity
// Barnes-Hut algorithm would be faster than this O(n^2) solution but the purpose of this program is mostly for
// playing around with less than 10 spheres
vector3D<double> Sphere::calculateNetGravity()
{
    static const double G = 6.674e-11;

    vector3D<double> sumOfGravityVector;
    sumOfGravityVector.load(0,0,0);

    for (Sphere* sphere : engine->spheres)
    {
        if (sphere == this) continue;

        vector3D<double> distanceVector = (sphere->position - position);
        double distance = this->distanceToSphere(sphere);

        if (distance == 0) continue;

        double F = G * ((mass * sphere->mass) / pow(std::max(distance, radius), 2));

        vector3D<double> gravityVector = distanceVector.unit() * F;
        sumOfGravityVector += gravityVector;
    }
    gravityVector = sumOfGravityVector * engine->gravityStrengthGui * engine->gravityStrength;
    return sumOfGravityVector * engine->gravityStrengthGui;
}

double Sphere::distanceToSphere(Sphere *sphere)
{
    vector3D<double> distanceVector = sphere->position - position;
    return sqrt(pow(distanceVector.x, 2)+pow(distanceVector.y,2)+pow(distanceVector.z,2));
}

void Sphere::createTrailSphere()
{
    TrailSphere* sphere = new TrailSphere(this);
    sphere->radius = radius / 5.0;
    sphere->position = position;
    trailSpheres.push_back(sphere);
}

void Sphere::killTrailSphere(TrailSphere *sphere)
{
    trailSpheres.erase(std::remove(trailSpheres.begin(), trailSpheres.end(), sphere), trailSpheres.end());
    delete sphere;
}