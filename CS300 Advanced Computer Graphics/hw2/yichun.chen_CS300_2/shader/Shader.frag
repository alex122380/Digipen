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

//in vec4 world_position;
//in vec4 world_normal;
//in vec2 TexCoord;
in vec4 ourColor;
in vec3 camera_normal;

//uniform vec4 eye_position;
//uniform vec3 diffuse_coefficient;
//uniform vec3 specular_coefficient;
//uniform float specular_exponent;
//uniform vec3 ambient_color;
//uniform vec4 light_position[8];
//uniform vec3 light_color[8];
//uniform int light_use[8];
uniform sampler2D ourTexture;
uniform bool mode;

out vec4 frag_color;

void main(void)
{
  //vec4 m = normalize(world_normal);
  //vec4 L;
  //vec4 V = normalize(eye_position - world_position);
  //vec4 RL;
  //vec3 amb_term = diffuse_coefficient * ambient_color; // Component wise multiplication.
  //vec3 diffuse_term;
  //vec3 specular_term;

  //frag_color = texture(ourTexture, TexCoord);
  
  //frag_color = vec4(amb_term, 1);
  
  //for (int i = 0; i < 8; ++i)
  //{
  //  if (light_use[i] == 1)
  //  {
  //    L = normalize(light_position[i] - world_position);
  //    RL = normalize(2 * dot(m, L) * m - L);
  //    diffuse_term = diffuse_coefficient * max(dot(m, L), 0.0) * light_color[i];
  //    specular_term = specular_coefficient * pow(max(dot(RL, V), 0.0), specular_exponent) * light_color[i];
  //    
  //    frag_color += vec4(diffuse_term + specular_term, 1);
  //  }
  //}

  //frag_color = vec4(1.0f, 1.0f, 0.0f, 1.0f);

  vec3 m = normalize(camera_normal);
  float shade = max(0, m.z);
  frag_color = shade * ourColor;

  //if (mode) // 1: color mode
  //{
  //  frag_color = ourColor; 
  //}
  //else // 0: texture mode
  //{
  //  frag_color = texture(ourTexture, TexCoord);
  //}
}