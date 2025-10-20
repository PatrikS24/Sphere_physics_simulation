//
// Created by patri on 20/10/2025.
//

#include "ImGuiLayer.h"
#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include <GL/freeglut.h>

void InitImGui()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplOpenGL3_Init("#version 330");
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
    ImGui::DestroyContext();
}