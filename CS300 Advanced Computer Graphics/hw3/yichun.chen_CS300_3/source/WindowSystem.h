/* Start Header -------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: WindowSystem.h
Purpose: Setup GLFW window.
Language: c++ / Visual Studio compiler 2019
Platform: Visual Studio compiler 2019 / Windows 10
Project: yichun.chen_CS300_1
Author: Yi-Chun Chen / yichun.chen / 180000819
Creation date: 09/28/2020
End Header --------------------------------------------------------*/

#pragma once

#ifndef WINDOW_SYSTEM_H
#define WINDOW_SYSTEM_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Camera.h"

class WindowSystem
{
  public:
    WindowSystem(const char *title, int width, int height);
    ~WindowSystem(void);
    void ProcessInput(void);
    int WindowShouldClose(void);
    void SwapBuffers(void);
    void PollEvents(void);
    int GetWidth() { return mWidth; }
    int GetHeight() { return mHeight; }

    GLFWwindow* GetWindow() const;
    Camera* currentCam;
    Camera* cam;
    Camera* camToRight;
    Camera* camToLeft;
    Camera* camToTop;
    Camera* camToBottom;
    Camera* camToFront;
    Camera* camToBack;

  private:
    const char *mTitle;
    int mWidth;
    int mHeight;
    GLFWwindow *mWindow;
};

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

#endif