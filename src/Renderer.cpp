//
// Created by patri on 20/10/2025.
//

#include "Camera.h"
#include "Renderer.h"
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "vector.h"
#include "Sphere.h"
#include "Globals.h"


GLuint fbo = 0;
GLuint colorTex = 0;
GLuint depthRb = 0;

void renderVector(const vector3D<double> &vector, const vector3D<double> &position, double radius, const vector3D<double> &color);
void renderAxis(int axis, vector3D<float> color);

void initRenderer()
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

void renderScene()
{
    // Draw to framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glViewport(0, 0, windowWidth - guiWidth, windowHeight);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glLoadIdentity();


    Camera *c = &engine->camera;
    if (c->trackedSphere != nullptr)
    {
        gluLookAt(  c->position.x, c->position.y, c->position.z,  // eye position
              c->trackedSphere->position.x, c->trackedSphere->position.y, c->trackedSphere->position.z,  // look at
              0.0, 1.0, 0.0); // up vector
    } else
    {
        gluLookAt(  c->position.x, c->position.y, c->position.z,  // eye position
              0.0, 0.0, 0.0,  // look at
              0.0, 1.0, 0.0); // up vector
    }


    /*
    *gluLookAt(0.0,0.0,30.0,  // eye position
    0.0, 0.0, 0.0,  // look at
    0.0, 1.0, 0.0); // up vector
    */

    // Render all spheres
    GLUquadric* quad = gluNewQuadric();
    gluQuadricNormals(quad, GLU_SMOOTH);

    for (Sphere* sphere : engine->spheres)
    {
        renderSphere(quad, sphere);

        glDisable(GL_LIGHTING);
        if (showVelocityVectors)
        {
            renderVector(sphere->velocity, sphere->position, sphere->radius, vector3D(39/255.0, 230/255.0, 45/255.0));
        }
        if (showGravityVectors)
        {
            renderVector(sphere->gravityVector, sphere->position, sphere->radius, vector3D(242/255.0, 22/255.0, 22/255.0));
        }
        if (showTrails)
        {
            renderTrailSpheres(quad, sphere);
        }
        glEnable(GL_LIGHTING);
    }

    gluDeleteQuadric(quad);

    glDisable(GL_LIGHTING);
    if (showXyzAxes)
    {
        renderAxis(0, vector3D(201/255.0, 77/255.0, 60/255.0)); // X axis
        renderAxis(1, vector3D(71/255.0, 186/255.0, 56/255.0)); // Y axis
        renderAxis(2, vector3D(56/255.0, 123/255.0, 186/255.0)); // Z axis
    }
    glEnable(GL_LIGHTING);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

void renderSphere(GLUquadric* quad, const Sphere* sphere)
{
    vector3D<double> sphereColor = sphere->color;
    glColor3f(sphereColor.x, sphereColor.y, sphereColor.z);

    glPushMatrix();
    glTranslatef(sphere->position.x, sphere->position.y, sphere->position.z);
    gluSphere(quad, sphere->radius, 32, 32);
    glPopMatrix();
}

void renderVector(const vector3D<double> &vector, const vector3D<double> &position, double radius, const vector3D<double> &color)
{
    vector3D<double> beginPosition = position + (unit(vector) * radius);
    vector3D<double> endPosition = beginPosition + vector;

    glColor3f(color.x,color.y,color.z);
    glPointSize(3.0);
    glLineWidth(5.0f);

    glBegin(GL_LINES);
    glVertex3d(beginPosition.x, beginPosition.y, beginPosition.z);
    glVertex3d(endPosition.x, endPosition.y, endPosition.z);
    glEnd();
}

void renderAxis(int axis, vector3D<float> color)
{
    vector3D<float> beginPosition = vector3D(0, 0, 0);
    beginPosition[axis] = -100;
    vector3D<float> endPosition = vector3D(0, 0, 0);
    endPosition[axis] = 100;

    glColor3f(color.x,color.y,color.z);
    glPointSize(3.0);
    glLineWidth(2.0f);

    glBegin(GL_LINES);
    glVertex3d(beginPosition.x, beginPosition.y, beginPosition.z);
    glVertex3d(endPosition.x, endPosition.y, endPosition.z);
    glEnd();
}

void createFramebuffer(int width, int height)
{
    if (fbo) {
        glDeleteFramebuffers(1, &fbo);
        glDeleteTextures(1, &colorTex);
        glDeleteRenderbuffers(1, &depthRb);
    }

    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    glGenTextures(1, &colorTex);
    glBindTexture(GL_TEXTURE_2D, colorTex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTex, 0);

    glGenRenderbuffers(1, &depthRb);
    glBindRenderbuffer(GL_RENDERBUFFER, depthRb);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, depthRb);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cerr << "Framebuffer not complete!\n";

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void renderTrailSpheres(GLUquadric* quad, const Sphere* sphere)
{
    for (TrailSphere *trail : sphere->trailSpheres)
    {
        glColor3f(1, 1, 1);

        glPushMatrix();
        glTranslatef(trail->position.x, trail->position.y, trail->position.z);
        gluSphere(quad, trail->radius, 8, 8);
        glPopMatrix();
    }
}
