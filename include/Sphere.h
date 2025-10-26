//
// Created by patri on 08/10/2025.
//

#ifndef C_PROGRAM_SPHERE_H
#define C_PROGRAM_SPHERE_H

#include <format>

#include "RigidBody.h"
#include "Engine.h"
#include <vector>
#include "TrailSphere.h"

class Engine;

class TrailSphere;

class Sphere : public RigidBody
{
    public:
        double radius{1};
        vector3D<double> color = vector3D<double>(219/255.0, 211/255.0, 245/255.0);
        std::vector<TrailSphere*> trailSpheres;

        ~Sphere();
        void update();
        double distanceToSphere(Sphere* sphere);
        vector3D<double> calculateNetGravity();
        void killTrailSphere(TrailSphere *sphere);

    private:
        void updatePosition();
        void updateVelocity();
        void applyGravity();
        void createTrailSphere();
};

#endif //C_PROGRAM_SPHERE_H