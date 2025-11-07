//
// Created by patri on 26/10/2025.
//

#include "Camera.h"
#include <cmath>
#include "Sphere.h"

void Camera::moveCamera(vector2D<double> move)
{
    // Move along the unit sphere surrounding the tracking object according to mouse movements
    double panSpeed = 0.005;
    theta += move.x * panSpeed;
    phi -= move.y * panSpeed;

    constexpr double PHI_MIN = 0.01;
    constexpr double PHI_MAX = M_PI - 0.01;

    phi = std::clamp(phi, PHI_MIN, PHI_MAX);

    vector3D<double> newPosition;
    newPosition.x = zoom * (cos(theta) * sin(phi));
    newPosition.y = zoom * (sin(theta) * sin(phi));
    newPosition.z = zoom * cos(phi);

    if (trackedSphere != nullptr)
    {
        newPosition += trackedSphere->position;
    }
    position = newPosition;
}

void Camera::update()
{
    vector3D<double> newPosition;
    newPosition.x = cos(theta) * sin(phi);
    newPosition.y = sin(theta) * sin(phi);
    newPosition.z = cos(phi);

    newPosition *= zoom;

    if (trackedSphere != nullptr)
    {
        newPosition += trackedSphere->position;
    }

    position = newPosition;
}
