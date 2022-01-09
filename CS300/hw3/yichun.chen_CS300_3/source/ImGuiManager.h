/* Start Header -------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: ImGuiManager.h
Purpose: Setup imGui and the program GUI.
Language: c++ / Visual Studio compiler 2019
Platform: Visual Studio compiler 2019 / Windows 10
Project: yichun.chen_CS300_1
Author: Yi-Chun Chen / yichun.chen / 180000819
Creation date: 09/28/2020
End Header --------------------------------------------------------*/

#pragma once

#ifndef IMGUI_MANAGER_H
#define IMGUI_MANAGER_H

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

class ImGuiManager
{
  public:
    ImGuiManager(GLFWwindow* window);
    ~ImGuiManager();
    void Update();
    int GetNormalDisplay();
    int GetCurrentModel();
    const char* GetCurrentModelName();
    int GetCurrentShader();

  private:
    int normalDisplay;
    int currentModel;
    const char *models[13] = { 
      "sphere.obj", "bunny.obj", "starwars1.obj", "cube.obj", "cube2.obj",
      "cup.obj", "sphere_modified.obj", "quad.obj", "rhino.obj", "triangle.obj",
      "lucy_princeton.obj", "bunny_high_poly.obj", "4Sphere.obj"
    };
    int currentShader;
};

#endif