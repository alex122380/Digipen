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

in vec4 ourColor;
in vec3 camera_normal;

uniform sampler2D ourTexture;
uniform bool mode;
uniform int textureNumber;

layout(location = 0)out vec4 frag_color_0;
layout(location = 1)out vec4 frag_color_1;
layout(location = 2)out vec4 frag_color_2;
layout(location = 3)out vec4 frag_color_3;
layout(location = 4)out vec4 frag_color_4;
layout(location = 5)out vec4 frag_color_5;

void main(void)
{
  vec3 m = normalize(camera_normal);
  float shade = max(0, m.z);

  if (textureNumber == 0)
  {
    frag_color_0 = shade * ourColor;
  }
  else if (textureNumber == 1)
  {
    frag_color_1 = shade * ourColor;
  }
  else if (textureNumber == 2)
  {
    frag_color_2 = shade * ourColor;
  }
  else if (textureNumber == 3)
  {
    frag_color_3 = shade * ourColor;
  }
  else if (textureNumber == 4)
  {
    frag_color_4 = shade * ourColor;
  }
  else if (textureNumber == 5)
  {
    frag_color_5 = shade * ourColor;
  } 
}