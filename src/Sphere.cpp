//
// Created by patri on 17/10/2025.
//

#include "Sphere.h"
#include "World.h"
#include <cstdlib>

static const double gravityStrenght = 100000000000;

Sphere::Sphere(World* _world)
{
    world = _world;
    velocity.load(0,0,0);
    acceleration.load(0,0,0);
}

void Sphere::update()
{
    applyGravity();
    updateVelocity();
    updatePosition();
}

void Sphere::updatePosition()
{
    position += velocity * world->deltaTime;
}

void Sphere::updateVelocity()
{
    velocity += acceleration * world->deltaTime;
}



void Sphere::applyGravity()
{
    vector3D<double> sumOfGravityVector = calculateNetGravity();
    vector3D<double> gravityAcceleration = sumOfGravityVector / mass;
    acceleration = gravityAcceleration * gravityStrenght;
}

vector3D<double> Sphere::calculateNetGravity()
{
    static const double G = 6.674e-11;

    vector3D<double> sumOfGravityVector;
    sumOfGravityVector.load(0,0,0);

    for (Sphere* sphere : world->spheres)
    {
        if (sphere == this) continue;

        vector3D<double> distanceVector = (sphere->position - position);
        double distance = sqrt(pow(distanceVector.x, 2)+pow(distanceVector.y,2)+pow(distanceVector.z,2));

        if (distance == 0) continue;

        double F = G * ((mass * sphere->mass) / pow(distance, 2));

        vector3D<double> gravityVector = distanceVector.unit() * F;
        sumOfGravityVector += gravityVector;
    }
    return sumOfGravityVector;
}

double Sphere::distanceToSphere(Sphere *sphere)
{
    vector3D<double> distanceVector = sphere->position - position;
    return sqrt(pow(distanceVector.x, 2)+pow(distanceVector.y,2)+pow(distanceVector.z,2));
}
