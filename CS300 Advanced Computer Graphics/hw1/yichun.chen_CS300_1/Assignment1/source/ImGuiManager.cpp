/* Start Header -------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: ImGuiManager.cpp
Purpose: Setup imGui and the program GUI.
Language: c++ / Visual Studio compiler 2019
Platform: Visual Studio compiler 2019 / Windows 10
Project: yichun.chen_CS300_1
Author: Yi-Chun Chen / yichun.chen / 180000819
Creation date: 09/28/2020
End Header --------------------------------------------------------*/

#include "ImGuiManager.h"

ImGuiManager::ImGuiManager(GLFWwindow* window) : normalDisplay(0), currentModel(0)
{
  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();
  // Setup Platform/Renderer bindings
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  const char* glsl_version = "#version 330";
  ImGui_ImplOpenGL3_Init(glsl_version);
  // Setup Dear ImGui style
  ImGui::StyleColorsDark();
}

ImGuiManager::~ImGuiManager()
{
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
}

void ImGuiManager::Update()
{
  // feed inputs to dear imgui, start new frame
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  // render your GUI
  ImGui::Begin("Options");
  ImGui::RadioButton("None", &normalDisplay, 0); ImGui::SameLine();
  ImGui::RadioButton("Vertex", &normalDisplay, 1); ImGui::SameLine();
  ImGui::RadioButton("Face", &normalDisplay, 2);
  ImGui::Combo("Model", &currentModel, models, IM_ARRAYSIZE(models));
  ImGui::End();

  // Render dear imgui into screen
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

int ImGuiManager::GetNormalDisplay()
{
  return normalDisplay;
}

int ImGuiManager::GetCurrentModel()
{
  return currentModel;
}

const char* ImGuiManager::GetCurrentModelName()
{
  return models[currentModel];
}