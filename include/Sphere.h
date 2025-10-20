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
        vector3D<double> color = vector3D<double>(0.7, 0.1, 0.1);
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