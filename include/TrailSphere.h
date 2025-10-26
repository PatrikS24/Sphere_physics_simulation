//
// Created by patri on 26/10/2025.
//

#ifndef C___PROGRAM_TRAILSPHERE_H
#define C___PROGRAM_TRAILSPHERE_H

#include "RigidBody.h"
#include "Sphere.h"

class Sphere;

class TrailSphere : public RigidBody
{
    public:
    double radius;
    int timeAlive{0};
    const int lifeTime{10000};
    Sphere *parent;
    TrailSphere(Sphere *p)
    {
        parent = p;
    };
    void update();
};

#endif //C___PROGRAM_TRAILSPHERE_H