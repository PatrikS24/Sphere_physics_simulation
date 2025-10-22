//
// Created by patri on 20/10/2025.
//

#ifndef C___PROGRAM_CALLBACKS_H
#define C___PROGRAM_CALLBACKS_H
#include <GL/glew.h>


void initGLUT(int argc, char** argv, int w, int h, const char* title);
void displayCallback();
void reshapeCallback(int w, int h);
void registerInputCallbacks();
void idleCallback();

#endif //C___PROGRAM_CALLBACKS_H