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
uniform mat4 modelView_matrix;

uniform bool light_on[16];
uniform vec4 light_position[16];
uniform vec3 ambient[16];
uniform vec3 diffuse[16];
uniform vec3 specular[16];
uniform float shininess[16];
    

out vec4 ourColor;

void main()
{
  int i;
  vec3 temp_color = vec3(0.0f, 0.0f, 0.0f);
  vec3 v = vec3(modelView_matrix * aPosition);
  vec3 N = normalize(mat3(normal_matrix) * aNormal);
  vec3 E = normalize(-v);

  for (i = 0; i < 16; ++i)
  {
    if (light_on[i])
    {
      vec3 L = normalize(light_position[i].xyz - v);
      vec3 R = normalize(2 * dot(N, L) * N - L);
      vec3 Ia = ambient[i];
      vec3 Id = diffuse[i] * max(dot(N, L), 0.0);
      vec3 Is = specular[i] * pow(max(dot(R, E), 0.0), shininess[i]);

      temp_color += Ia + Id + Is;
    }
  }

  ourColor = vec4(temp_color, 1.0f);

  gl_Position = persp_matrix * view_matrix * model_matrix * aPosition;
}