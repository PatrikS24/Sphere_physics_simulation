//
// Created by patri on 20/10/2025.
//

#ifndef C___PROGRAM_RENDERER_H
#define C___PROGRAM_RENDERER_H
#include "vector.h"
#include "Sphere.h"
#include <GL/freeglut.h>

void InitRenderer();
void DrawScene();
void renderSphere(GLUquadric* quad, Sphere* sphere);

#endif //C___PROGRAM_RENDERER_H