//
// Created by patri on 20/10/2025.
//
#include "Callbacks.h"
#include "Renderer.h"
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "ImGuiLayer.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_glut.cpp"

#include "Globals.h"

void initGLUT(int argc, char** argv, int w, int h, const char* title)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(w, h);
    glutCreateWindow(title);

}

void idleCallback() {
    glutPostRedisplay();  // Tell GLUT "please call display() again soon"
}

void displayCallback()
{
    //BeginImGuiFrame();
    renderScene();
    renderImGui();

    engine->update();

    /*
    // Example ImGui window
    ImGui::Begin("Stats");
    ImGui::Text("FPS: %.1f", engine->fps);
    ImGui::End();
    */

    EndImGuiFrame();
    glutSwapBuffers();
}

void reshapeCallback(int w, int h)
{
    windowWidth = w;
    windowHeight = h;
    guiWidth = w * guiAspect;

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)(w - guiWidth)/ (double)h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    createFramebuffer(w - guiWidth, h);
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
    ImGui_ImplGLUT_KeyboardFunc(key, x, y);
}


void registerInputCallbacks()
{
    // set mouse/keyboard callbacks here
    glutMouseFunc(mouseCallback);
    glutMotionFunc(motionCallback);
    glutPassiveMotionFunc(motionCallback);
    glutKeyboardFunc(keyboardCallback);
}