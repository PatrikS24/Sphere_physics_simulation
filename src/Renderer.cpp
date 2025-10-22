//
// Created by patri on 20/10/2025.
//

#include "Renderer.h"
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "vector.h"
#include "Sphere.h"
#include "Globals.h"

GLuint fbo = 0;
GLuint colorTex = 0;
GLuint depthRb = 0;

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

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

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
