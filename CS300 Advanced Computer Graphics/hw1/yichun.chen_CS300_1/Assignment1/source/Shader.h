/* Start Header -------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: Shader.h
Purpose: Initialize shader program.
Language: c++ / Visual Studio compiler 2019
Platform: Visual Studio compiler 2019 / Windows 10
Project: yichun.chen_CS300_1
Author: Yi-Chun Chen / yichun.chen / 180000819
Creation date: 09/28/2020
End Header --------------------------------------------------------*/

#pragma once

#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <string>

// Reference:
// https://learnopengl.com/code_viewer_gh.php?code=includes/learnopengl/shader_s.h
// 
class Shader
{
public:
  Shader(const char *vertexPath, const char *fragmentPath);
  ~Shader();
  void UseProgram();
  GLint GetUniformLocation(const std::string &name);

private:
  GLint programID;
  void CheckCompileErrors(unsigned int shader, std::string type);
};

#endif