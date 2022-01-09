/* Start Header -------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: Shader.vs
Purpose: Vertex shader.
Language: c++ / Visual Studio compiler 2019
Platform: Visual Studio compiler 2019 / Windows 10
Project: yichun.chen_CS300_1
Author: Yi-Chun Chen / yichun.chen / 180000819
Creation date: 09/28/2020
End Header --------------------------------------------------------*/

#version 330 core

layout (location = 0) in vec4 aPosition;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec4 aColor;
layout (location = 3) in vec3 aNormal;

uniform mat4 persp_matrix;
uniform mat4 view_matrix;
uniform mat4 model_matrix;
uniform mat4 normal_matrix;

//out vec4 world_position;
//out vec4 world_normal;
//out vec2 TexCoord;
out vec4 ourColor;
out vec3 camera_normal;

void main()
{
  gl_Position = persp_matrix * view_matrix * model_matrix * aPosition;
  //world_position = model_matrix * position;
  //world_normal = normal_matrix * normal;
  //TexCoord = aTexCoord;
  ourColor = aColor;
  camera_normal = mat3(view_matrix) * mat3(normal_matrix) * aNormal;
}