//
// Created by patri on 20/10/2025.
//

#include "ImGuiLayer.h"
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_glut.h"
#include "Globals.h"
#include "Renderer.h"

void renderSimulationGui();
void renderGeneralPropertiesGui();
void renderSpherePropertiesGui(int id, Sphere* sphere);
void renderFpsCounter();

void initImGui()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGLUT_Init();
    ImGui_ImplGLUT_InstallFuncs();
    ImGui_ImplOpenGL3_Init("#version 330");

    createFramebuffer(windowWidth - guiWidth, windowHeight);
}

void renderImGui()
{
    int w = glutGet(GLUT_WINDOW_WIDTH);
    int h = glutGet(GLUT_WINDOW_HEIGHT);
    windowWidth = (w > 0) ? w : 1;
    windowHeight = (h > 0) ? h : 1;
    guiWidth = (guiWidth > 0) ? guiWidth : 1;

    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize = ImVec2((float)windowWidth, (float)windowHeight);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGLUT_NewFrame();
    ImGui::NewFrame();

    renderGeneralPropertiesGui();
    renderSimulationGui();
    renderFpsCounter();

    ImGui::Render();
    glViewport(0, 0, windowWidth, windowHeight);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void renderGeneralPropertiesGui()
{
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(guiWidth, windowHeight));
    ImGui::Begin("Properties", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);

    if (engine->paused)
    {
        ImGui::PushStyleColor(21, ImVec4(71/255.0f, 166/255.0f, 50/255.0f, 1));
        if (ImGui::Button("Run"))
        {
            engine->paused = false;
        }
        ImGui::PopStyleColor();
    }
    else
    {
        ImGui::PushStyleColor(21, ImVec4(166/255.0f, 58/255.0f, 50/255.0f, 1));
        if (ImGui::Button("Pause"))
        {
            engine->paused = true;
        }
        ImGui::PopStyleColor();
    }

    double min = 0.0;
    double max = 5.0;
    ImGui::SliderScalar("Simulation Speed", ImGuiDataType_Double, &engine->simulationSpeed, &min, &max);
    ImGui::SliderFloat("Gravity Strength", &engine->gravityStrengthGui, 0.0f, 10.0f);
    ImGui::Checkbox("Show Velocity Vectors", &showVelocityVectors);
    ImGui::Checkbox("Show gravity Vectors", &showGravityVectors);
    ImGui::Checkbox("Show xyz Axes", &showXyzAxes);

    if (!engine->paused)
    {
        ImGui::BeginDisabled();
    }
    if (ImGui::Button("Add Sphere"))
    {
        engine->createSphere();
    }
    if (!engine->paused)
    {
        ImGui::EndDisabled();
    }

    // Sphere properties
    ImGui::BeginChild("Spheres", ImVec2(0,0), ImGuiWindowFlags_NoResize);
    ImGui::Text("Spheres");

    for (int i = 0; i < engine->spheres.size(); i++)
    {
        renderSpherePropertiesGui(i, engine->spheres[i]);
    }

    ImGui::EndChild();

    ImGui::End();
}

void renderSpherePropertiesGui(int id, Sphere* sphere)
{
    char childName[16];
    sprintf(childName, "Sphere %d", id);
    ImGui::BeginChild(childName, ImVec2(0, 155), true);

    if (!engine->paused)
    {
        ImGui::BeginDisabled();
    }

    sprintf(childName, "Sphere %d", id + 1);
    ImGui::Text(childName);

    double min = 0;
    double max = 1000;
    ImGui::DragScalar("Mass", ImGuiDataType_Double, &sphere->mass, 0.5f, &min, &max);

    min = 0;
    max = 20;
    ImGui::DragScalar("Radius", ImGuiDataType_Double, &sphere->radius, 0.2f, &min, &max);

    min = -20;
    max = 20;
    ImGui::DragScalarN("Position", ImGuiDataType_Double, &sphere->position, 3, 0.1f, &min, &max);

    min = -20;
    max = 20;
    ImGui::DragScalarN("Velocity", ImGuiDataType_Double, &sphere->velocity, 3, 0.1f, &min, &max);

    if (ImGui::Button("Remove"))
    {
        engine->spheres.erase(engine->spheres.begin() + id);
        delete sphere;
    }

    if (!engine->paused)
    {
        ImGui::EndDisabled();
    }

    ImGui::EndChild();
}

void renderSimulationGui()
{
    ImGui::SetNextWindowSize(ImVec2(windowWidth - guiWidth, windowHeight));
    ImGui::SetNextWindowPos(ImVec2(guiWidth, 0));
    ImGui::Begin("Scene Viewer", 0, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar);

    ImGui::SetCursorPos(ImVec2(0, 0));

    ImVec2 size(windowWidth - guiWidth, windowHeight);
    ImGui::Image((void*)(intptr_t)colorTex, size, ImVec2(0, 1), ImVec2(1, 0));

    ImGui::End();
}

void renderFpsCounter()
{
    ImGui::SetNextWindowSize(ImVec2(90, 20));
    ImGui::SetNextWindowPos(ImVec2(windowWidth - 90 - 10, 10));
    ImGui::Begin("FpsCounter", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
    ImGui::Text("FPS: %d", engine->fps);
    ImGui::End();
}

void BeginImGuiFrame()
{
    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize = ImVec2(
        (float)glutGet(GLUT_WINDOW_WIDTH),
        (float)glutGet(GLUT_WINDOW_HEIGHT)
    );
    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();
}

void EndImGuiFrame()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ShutdownImGui()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGLUT_Shutdown();
    ImGui::DestroyContext();
}