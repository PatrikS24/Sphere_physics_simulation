//
// Created by patri on 20/10/2025.
//

#ifndef C___PROGRAM_RENDERER_H
#define C___PROGRAM_RENDERER_H
#include "vector.h"
#include "Sphere.h"
#include <GL/glew.h>
#include <GL/freeglut.h>


extern GLuint fbo;
extern GLuint colorTex;
extern GLuint depthRb;

void initRenderer();
void renderScene();
void renderSphere(GLUquadric* quad, Sphere* sphere);
void createFramebuffer(int width, int height);

#endif //C___PROGRAM_RENDERER_H