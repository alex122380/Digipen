/* Start Header -------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: LightSource.cpp
Purpose: Define light source structure.
Language: c++ / Visual Studio compiler 2019
Platform: Visual Studio compiler 2019 / Windows 10
Project: yichun.chen_CS300_2
Author: Yi-Chun Chen / yichun.chen / 180000819
Creation date: 11/17/2020
End Header --------------------------------------------------------*/

#include "LightSource.h"

LightSource::LightSource(int Id, bool lightOn, glm::vec4 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess)
                        : Id_(Id), lightOn_(lightOn), position_(position), ambient_(ambient), diffuse_(diffuse), specular_(specular), shininess_(shininess)
{

}

int LightSource::GetId()
{
  return Id_;
}

bool LightSource::GetLightOn()
{
  return lightOn_;
}

glm::vec4 LightSource::GetPosition()
{
  return position_;
}

glm::vec3 LightSource::GetAmbient()
{
  return ambient_;
}

glm::vec3 LightSource::GetDiffuse()
{
  return diffuse_;
}

glm::vec3 LightSource::GetSpecular()
{
  return specular_;
}

float LightSource::GetShininess()
{
  return shininess_;
}

void LightSource::SetLightOn(bool lightOn)
{
  lightOn_ = lightOn;
}

void LightSource::SetPosition(glm::vec4 pos)
{
  position_ = pos;
}