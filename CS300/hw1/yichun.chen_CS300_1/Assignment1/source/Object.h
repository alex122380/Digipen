/* Start Header -------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: Object.h
Purpose: Load .obj file, scale it to [-1..1] and calculates the normals.
Language: c++ / Visual Studio compiler 2019
Platform: Visual Studio compiler 2019 / Windows 10
Project: yichun.chen_CS300_1
Author: Yi-Chun Chen / yichun.chen / 180000819
Creation date: 09/28/2020
End Header --------------------------------------------------------*/

#pragma once

#ifndef OBJECT_LOADER_H
#define OBJECT_LOADER_H

#include <vector>
#include "MeshData.h"
#include <map>

class Object
{
  public:
    Object(const char * modelName);
    Object(MeshData *md);
    ~Object();
    std::vector<MeshData::Vertex>& GetVertices();
    std::vector<unsigned int>& GetIndices();
    void ScaleTo(float lowerBound, float higherBound);
    void CalculateNormal();

  private:
    float maxX, minX, maxY, minY, maxZ, minZ;
    std::vector<MeshData::Vertex> vertices_;
    std::vector<unsigned int> indices_;
    std::map<unsigned int, std::vector<glm::vec3>> normalMap_;
};

#endif