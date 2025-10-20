//
// Created by patri on 20/10/2025.
//

#include "Renderer.h"
#include <GL/freeglut.h>
#include "vector.h"
#include "Sphere.h"
#include "Globals.h"

void InitRenderer()
{
    // setup shaders, load textures, etc.
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);

    GLfloat light_pos[] = { 2.0f, 2.0f, 2.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
}

void DrawScene()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Position the camera
    gluLookAt(0.0, 0.0, 30.0,  // eye position
              0.0, 0.0, 0.0,  // look at
              0.0, 1.0, 0.0); // up vector

    // Render all spheres
    GLUquadric* quad = gluNewQuadric();
    gluQuadricNormals(quad, GLU_SMOOTH);

    for (Sphere* sphere : engine->spheres)
    {
        renderSphere(quad, sphere);
    }

    gluDeleteQuadric(quad);

}

void renderSphere(GLUquadric* quad, Sphere* sphere)
{
    vector3D<double> sphereColor = sphere->color;
    glColor3f(sphereColor.x, sphereColor.y, sphereColor.z);

    glPushMatrix();
    glTranslatef(sphere->position.x, sphere->position.y, sphere->position.z);
    gluSphere(quad, sphere->radius, 32, 32);
    glPopMatrix();
}