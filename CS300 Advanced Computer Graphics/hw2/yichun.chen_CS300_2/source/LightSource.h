/* Start Header -------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: LightSource.h
Purpose: Define light source structure.
Language: c++ / Visual Studio compiler 2019
Platform: Visual Studio compiler 2019 / Windows 10
Project: yichun.chen_CS300_2
Author: Yi-Chun Chen / yichun.chen / 180000819
Creation date: 11/17/2020
End Header --------------------------------------------------------*/

#pragma once

#ifndef LIGHT_SOURCE_H
#define LIGHT_SOURCE_H

#include <glm/glm.hpp>

class LightSource
{
  public:
    LightSource(int Id, bool lightOn, glm::vec4 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess);
    int GetId();
    bool GetLightOn();
    glm::vec4 GetPosition();
    glm::vec3 GetAmbient();
    glm::vec3 GetDiffuse();
    glm::vec3 GetSpecular();
    float GetShininess();
    void SetLightOn(bool lightOn);
    void SetPosition(glm::vec4 pos);

  private:
    int Id_;
    bool lightOn_;
    glm::vec4 position_;
    glm::vec3 ambient_;
    glm::vec3 diffuse_;
    glm::vec3 specular_;
    float shininess_;
};

#endif