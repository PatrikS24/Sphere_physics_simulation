//
// Created by patri on 20/10/2025.
//
#include "Callbacks.h"
#include "Renderer.h"
#include <GL/glew.h>
#include "ImGuiLayer.h"
#include "backends/imgui_impl_opengl3.h"

#include "Globals.h"

void initGLUT(int argc, char** argv, int w, int h, const char* title)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(w, h);
    glutCreateWindow(title);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
}

void idleCallback() {
    glutPostRedisplay();  // Tell GLUT "please call display() again soon"
}

void displayCallback()
{
    BeginImGuiFrame();
    renderScene();

    engine->update();

    // Example ImGui window
    ImGui::Begin("Stats");
    ImGui::Text("FPS: %.1f", engine->fps);
    ImGui::End();

    EndImGuiFrame();
    glutSwapBuffers();
}

void reshapeCallback(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void mouseCallback(int button, int state, int x, int y)
{
    ImGuiIO& io = ImGui::GetIO();
    io.AddMouseButtonEvent(button, state == GLUT_DOWN);
}

void motionCallback(int x, int y)
{
    ImGuiIO& io = ImGui::GetIO();
    io.AddMousePosEvent((float)x, (float)y);
}

void keyboardCallback(unsigned char key, int x, int y)
{
    ImGuiIO& io = ImGui::GetIO();
    io.AddInputCharacter(key);
}


void registerInputCallbacks()
{
    // set mouse/keyboard callbacks here
    glutMouseFunc(mouseCallback);
    glutMotionFunc(motionCallback);
    glutPassiveMotionFunc(motionCallback);
    glutKeyboardFunc(keyboardCallback);
}