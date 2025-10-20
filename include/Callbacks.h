//
// Created by patri on 20/10/2025.
//

#ifndef C___PROGRAM_CALLBACKS_H
#define C___PROGRAM_CALLBACKS_H

void InitGLUT(int argc, char** argv, int w, int h, const char* title);
void DisplayCallback();
void ReshapeCallback(int w, int h);
void RegisterInputCallbacks();
void idleCallback();

#endif //C___PROGRAM_CALLBACKS_H