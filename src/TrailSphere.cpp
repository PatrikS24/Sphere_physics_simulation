//
// Created by patri on 26/10/2025.
//

#include "TrailSphere.h"


void TrailSphere::update()
{
    timeAlive++;
    if (radius > 0)
    {
        radius -= 0.0002;
    }
    if (timeAlive > lifeTime || radius <= 0)
    {
        parent->killTrailSphere(this);
    }
}
