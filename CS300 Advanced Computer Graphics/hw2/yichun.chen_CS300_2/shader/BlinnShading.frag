/* Start Header -------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: Shader.fs
Purpose: Fragment shader.
Language: c++ / Visual Studio compiler 2019
Platform: Visual Studio compiler 2019 / Windows 10
Project: yichun.chen_CS300_1
Author: Yi-Chun Chen / yichun.chen / 180000819
Creation date: 09/28/2020
End Header --------------------------------------------------------*/

#version 330 core

in vec3 v;
in vec3 N;

uniform bool light_on[16];
uniform vec4 light_position[16];
uniform vec3 ambient[16];
uniform vec3 diffuse[16];
uniform vec3 specular[16];
uniform float shininess[16];

out vec4 frag_color;

void main(void)
{
  int i;
  vec3 temp_color = vec3(0.0f, 0.0f, 0.0f);
  vec3 E = normalize(-v);

  for (i = 0; i < 16; ++i)
  {
    if (light_on[i])
    {
      vec3 L = normalize(light_position[i].xyz - v);
      vec3 H = normalize(L + E);
      vec3 Ia = ambient[i];
      vec3 Id = diffuse[i] * max(dot(N, L), 0.0);
      vec3 Is = specular[i] * pow(max(dot(N, H), 0.0), shininess[i]);

      temp_color += Ia + Id + Is;
    }
  }

  frag_color = vec4(temp_color, 1.0f);
}