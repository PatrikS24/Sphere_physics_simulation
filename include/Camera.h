//
// Created by patri on 26/10/2025.
//
#pragma once

#include "Vector.h"
class Sphere;
class Camera
{
    public:
    vector3D<double> position;
    double phi;
    double theta;
    Sphere *trackingObject;
    double zoom;

    void moveCamera(vector2D<double> move);
    void update();
};