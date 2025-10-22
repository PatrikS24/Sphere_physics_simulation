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
}

void renderGeneralPropertiesGui()
{
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(guiWidth, windowHeight));
    ImGui::Begin("Properties", NULL, ImGuiWindowFlags_NoCollapse);

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

    ImGui::End();
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

    ImGui::Render();
    glViewport(0, 0, windowWidth, windowHeight);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
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