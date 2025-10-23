//
// Created by patri on 20/10/2025.
//

#ifndef C___PROGRAM_GLOBALS_H
#define C___PROGRAM_GLOBALS_H

#include "Engine.h"
#include <GL/glew.h>

extern Engine *engine;
extern int windowWidth;
extern int windowHeight;
extern int guiWidth;

extern bool showVelocityVectors;
extern bool showGravityVectors;
extern bool showXyzAxes;

// Framebuffer
extern GLuint fbo;
extern GLuint colorTex;
extern GLuint depthRb;

#endif //C___PROGRAM_GLOBALS_H