#include <GL/glew.h>

#include "Callbacks.h"
#include "Renderer.h"
#include "ImGuiLayer.h"

#include "Engine.h"
#include "include/Sphere.h"


Engine *engine = nullptr;
int windowWidth = 800;
int windowHeight = 600;
int guiWidth = 349;

bool showVelocityVectors = false;
bool showGravityVectors = false;
bool showXyzAxes = false;
bool showTrails = false;


int main(int argc, char** argv) {
    engine = new Engine();

    engine->initEngine();

    initGLUT(argc, argv, windowWidth, windowHeight, "Sphere physics simulation");
    glewInit();

    initRenderer();
    initImGui();

    glutDisplayFunc(displayCallback);
    glutReshapeFunc(reshapeCallback);
    glutIdleFunc(idleCallback);
    registerInputCallbacks();

    glutMainLoop();

    ShutdownImGui();

    delete engine;
    return 0;
}