/* Start Header -------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: WindowSystem.cpp
Purpose: Setup GLFW window.
Language: c++ / Visual Studio compiler 2019
Platform: Visual Studio compiler 2019 / Windows 10
Project: yichun.chen_CS300_1
Author: Yi-Chun Chen / yichun.chen / 180000819
Creation date: 09/28/2020
End Header --------------------------------------------------------*/

#include <iostream>
#include "WindowSystem.h"

WindowSystem::WindowSystem(const char *title, int width, int height) : mTitle(title), mWidth(width), mHeight(height)
{
  // Reference:
  // https://learnopengl.com/
  // https://github.com/JoeyDeVries/LearnOpenGL/tree/master/src
  //

  // Initialize window.
  // ----------------------------------------------------------------
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  // glfw window creation
  // --------------------
  mWindow = glfwCreateWindow(mWidth, mHeight, mTitle, NULL, NULL);
  if (mWindow == NULL)
  {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    // Some exception handling here.
  }
  glfwMakeContextCurrent(mWindow);
  glfwSetFramebufferSizeCallback(mWindow, framebuffer_size_callback);

  // glad: load all OpenGL function pointers
  // ---------------------------------------
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "Failed to initialize GLAD" << std::endl;
    // Some exception handling here.
  }

  //Camera cam1 = Camera(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 90.0f, (float)mWidth / (float)mHeight, 0.1f, 100.0f);
  //Camera cam2 = Camera(glm::vec3(-10.0f, 0.0f, 10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 90.0f, (float)mWidth / (float)mHeight, 0.1f, 1000.0f);
  cam = new Camera(glm::vec3(-3.0f, 3.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 60.0f, (float)mWidth / (float)mHeight, 0.1f, 1000.0f);
}

WindowSystem::~WindowSystem(void)
{
  // Reference:
  // https://learnopengl.com/
  // https://github.com/JoeyDeVries/LearnOpenGL/tree/master/src
  //

  // glfw: terminate, clearing all previously allocated GLFW resources.
  // ------------------------------------------------------------------
  glfwTerminate();
  delete cam;
}

void WindowSystem::ProcessInput(void)
{
  if (glfwGetKey(mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
  {
    glfwSetWindowShouldClose(mWindow, true);
  }
}

int WindowSystem::WindowShouldClose(void)
{
  return glfwWindowShouldClose(mWindow);
}

void WindowSystem::SwapBuffers(void)
{
  glfwSwapBuffers(mWindow);
}

void WindowSystem::PollEvents(void)
{
  glfwPollEvents();
}

GLFWwindow* WindowSystem::GetWindow() const
{
  return mWindow;
}

// Non-class function.
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
  glViewport(0, 0, width, height);
}