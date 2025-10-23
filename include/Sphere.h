//
// Created by patri on 08/10/2025.
//

#ifndef C_PROGRAM_SPHERE_H
#define C_PROGRAM_SPHERE_H

#include "RigidBody.h"
#include "Engine.h"

class Engine;

class Sphere : public RigidBody
{
    public:
        double radius{1};
        vector3D<double> color = vector3D<double>(166/255.0f, 227/255.0f, 1);
        void update();
        void collision();
        double distanceToSphere(Sphere* sphere);
        vector3D<double> calculateNetGravity();

    private:
        void updatePosition();
        void updateVelocity();
        void applyGravity();
};

#endif //C_PROGRAM_SPHERE_H