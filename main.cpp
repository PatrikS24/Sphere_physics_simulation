#include <GL/glew.h>

#include "Callbacks.h"
#include "Renderer.h"
#include "ImGuiLayer.h"

#include "Engine.h"
#include "include/Sphere.h"


Engine *engine = nullptr;
int windowWidth = 800;
int windowHeight = 600;
float guiAspect = 1 / 3.5f;
int guiWidth = windowWidth * guiAspect;

bool showVelocityVectors = false;
bool showGravityVectors = false;
bool showXyzAxes = false;


int main(int argc, char** argv) {
    engine = new Engine();


    Sphere *sphere1 = new Sphere();
    Sphere *sphere2 = new Sphere();
    sphere2->position.x = 4;
    sphere1->velocity = vector3D<double>(0, 0, 0);
    sphere2->velocity = vector3D<double>(0, -5, 0);
    sphere1->radius = 2;
    sphere2->radius = 0.5;
    sphere1->mass = 10;

    Sphere *sphere3 = new Sphere();
    sphere3->position.x = -4;
    sphere3->velocity = vector3D<double>(0, 5, 0);

    engine->spheres.push_back(sphere1);
    engine->spheres.push_back(sphere2);
    engine->spheres.push_back(sphere3);


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
    delete sphere1;
    delete sphere2;
    delete sphere3;
    return 0;
}