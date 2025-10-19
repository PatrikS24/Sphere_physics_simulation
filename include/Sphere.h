//
// Created by patri on 08/10/2025.
//

#ifndef C_PROGRAM_SPHERE_H
#define C_PROGRAM_SPHERE_H

#include "RigidBody.h"
#include "World.h"

class World;

class Sphere : public RigidBody
{
    public:
        World *world;
        double radius{1};
        explicit Sphere(World* _world);
        void update();
        void collision();
        double distanceToSphere(Sphere* sphere);

    private:
        void updatePosition();
        void updateVelocity();
        void applyGravity();
        vector3D<double> calculateNetGravity();
};

#endif //C_PROGRAM_SPHERE_H