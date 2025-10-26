//
// Created by patri on 26/10/2025.
//

#include "Camera.h"
#include <cmath>
#include "Sphere.h"

void Camera::moveCamera(vector2D<double> move)
{
    // Move along the unit sphere surrounding the tracking object
    double panSpeed = 0.005;
    theta -= move.x * panSpeed / std::max(std::abs(std::sin(phi)), 1e-6);
    phi -= move.y * panSpeed;

    constexpr double PHI_MIN = 0.01;
    constexpr double PHI_MAX = M_PI - 0.01;

    if (phi < PHI_MIN)
        phi = PHI_MIN;
    else if (phi > PHI_MAX)
        phi = PHI_MAX;

    vector3D<double> newPosition;
    newPosition.x = (cos(theta) * sin(phi));
    newPosition.y = (sin(theta) * sin(phi));
    newPosition.z = cos(phi);

    if (trackedSphere != nullptr)
    {
        newPosition += trackedSphere->position;
    }

    position = newPosition * zoom;
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
