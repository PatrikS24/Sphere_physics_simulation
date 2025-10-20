#include <GL/glut.h>
#include <GL/glu.h>

#include "World.h"
#include "include/Sphere.h"

#include "libs/imgui/imgui.h"
#include "libs/imgui/backends/imgui_impl_opengl3.h"

// Window size
int width = 800;
int height = 600;

double physicsSpeed = 0.001;

// fps counter variables
int frameCount = 0;
static int previousTime = 0;
float fps = 0;

World *world;

void init() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);

    GLfloat light_pos[] = { 2.0f, 2.0f, 2.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
}

void idle() {
    glutPostRedisplay();  // Tell GLUT "please call display() again soon"
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

void calculateFps()
{
    frameCount++;

    int currentTime = glutGet(GLUT_ELAPSED_TIME);
    int timeInterval = currentTime - previousTime;

    if (timeInterval > 1000) {
        fps = frameCount / (timeInterval / 1000.0f);
        previousTime = currentTime;
        frameCount = 0;
    }
}

void calcualateDeltaTime()
{
    static int lastTime = 0;
    int currentTime = glutGet(GLUT_ELAPSED_TIME);
    int deltaTime = (currentTime - lastTime);
    lastTime = currentTime;
    world->deltaTime = deltaTime * physicsSpeed;
}

void display() {

    ImGuiIO& io = ImGui::GetIO();
    int width = glutGet(GLUT_WINDOW_WIDTH);
    int height = glutGet(GLUT_WINDOW_HEIGHT);
    io.DisplaySize = ImVec2((float)width, (float)height);


    // Start a new ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Position the camera
    gluLookAt(0.0, 0.0, 30.0,  // eye position
              0.0, 0.0, 0.0,  // look at
              0.0, 1.0, 0.0); // up vector

    // Main functions
    calcualateDeltaTime();
    calculateFps();
    world->update();

    // Render spheres
    GLUquadric* quad = gluNewQuadric();
    gluQuadricNormals(quad, GLU_SMOOTH);

    for (Sphere* sphere : world->spheres)
    {
        renderSphere(quad, sphere);
    }

    gluDeleteQuadric(quad);


    // Add an ImGui window
    ImGui::Begin("ImGui Overlay");
    ImGui::Text("FPS: %.1f", fps);
    ImGui::End();

    // Render ImGui on top of your scene
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());



    glutSwapBuffers();
}

void reshape(int w, int h) {
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


void registerImguiCallbacks()
{
    glutMouseFunc(mouseCallback);
    glutMotionFunc(motionCallback);
    glutPassiveMotionFunc(motionCallback);
    glutKeyboardFunc(keyboardCallback);
}

int main(int argc, char** argv) {
    world = new World();
    static Sphere sphere1(world);
    static Sphere sphere2(world);
    sphere2.position.x = 4;
    sphere1.velocity = vector3D<double>(0, 0, 0);
    sphere2.velocity = vector3D<double>(0, -5, 0);
    sphere1.radius = 2;
    sphere2.radius = 0.5;
    sphere1.mass = 10;

    world->spheres.push_back(&sphere1);
    world->spheres.push_back(&sphere2);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutCreateWindow("Sphere physics simulation");

    init();
    registerImguiCallbacks();
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutReshapeFunc(reshape);


    // After setting up GLUT + OpenGL:
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    // Initialize ImGui OpenGL backend
    ImGui_ImplOpenGL3_Init("#version 330");

    glutMainLoop();


    ImGui_ImplOpenGL3_Shutdown();
    ImGui::DestroyContext();

    delete world;
    return 0;
}