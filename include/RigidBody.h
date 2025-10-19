//
// Created by patri on 08/10/2025.
//

#ifndef C_PROGRAM_RIGIDBODY_H
#define C_PROGRAM_RIGIDBODY_H

#include "TransformStructs.h"
#include "Vector.h"

class RigidBody
{
    public:
        vector3D<double> position;
        Rotation rotation;
        vector3D<double> velocity;
        vector3D<double> acceleration;
        Scale scale;
        double mass{1};
};

#endif