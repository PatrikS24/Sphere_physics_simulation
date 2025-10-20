#include "Callbacks.h"
#include "Renderer.h"
#include "ImGuiLayer.h"

#include "Engine.h"
#include "include/Sphere.h"


Engine *engine = nullptr;


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

    engine->spheres.push_back(sphere1);
    engine->spheres.push_back(sphere2);

    InitGLUT(argc, argv, 800, 400, "Sphere physics simulation");

    InitRenderer();
    InitImGui();

    glutDisplayFunc(DisplayCallback);
    glutReshapeFunc(ReshapeCallback);
    glutIdleFunc(idleCallback);
    RegisterInputCallbacks();

    glutMainLoop();

    ShutdownImGui();

    delete engine;
    delete sphere1;
    delete sphere2;
    return 0;
}