/* Start Header -------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: Object.cpp
Purpose: Load .obj file, scale it to [-1..1] and calculates the normals.
Language: c++ / Visual Studio compiler 2019
Platform: Visual Studio compiler 2019 / Windows 10
Project: yichun.chen_CS300_1
Author: Yi-Chun Chen / yichun.chen / 180000819
Creation date: 09/28/2020
End Header --------------------------------------------------------*/

#include "Object.h"
#include <fstream>
#include <sstream>
#include <string>
#include <limits>
#include <numeric>

Object::Object(const char *modelName) : maxX(-std::numeric_limits<float>::infinity()), minX(std::numeric_limits<float>::infinity()),
                                       maxY(-std::numeric_limits<float>::infinity()), minY(std::numeric_limits<float>::infinity()),
                                       maxZ(-std::numeric_limits<float>::infinity()), minZ(std::numeric_limits<float>::infinity()),
                                       normalMap_(std::map<unsigned int, std::vector<glm::vec3>>())
{
  std::string dir = { "model/" };
  dir += modelName;
  std::ifstream infile(dir);

  std::string line;
  while (std::getline(infile, line))
  {
    std::istringstream iss(line);
    std::string token;
    iss >> token;
    if (token == "v")
    {
      MeshData::Vertex vertex;

      iss >> token;
      vertex.Position.x = std::stof(token);
      if (vertex.Position.x > maxX)
        maxX = vertex.Position.x;
      if (vertex.Position.x < minX)
        minX = vertex.Position.x;

      iss >> token;
      vertex.Position.y = std::stof(token);
      if (vertex.Position.y > maxY)
        maxY = vertex.Position.y;
      if (vertex.Position.y < minY)
        minY = vertex.Position.y;

      iss >> token;
      vertex.Position.z = std::stof(token);
      if (vertex.Position.z > maxZ)
        maxZ = vertex.Position.z;
      if (vertex.Position.z < minZ)
        minZ = vertex.Position.z;

      vertices_.push_back(vertex);
    }
    else if (token == "f")
    {
      unsigned int fanPivot, fanRight, fanLeft;

      iss >> token;
      fanPivot = std::stoul(token) - 1;
      indices_.push_back(fanPivot);

      iss >> token;
      fanRight = std::stoul(token) - 1;
      indices_.push_back(fanRight);

      iss >> token;
      fanLeft = std::stoul(token) - 1;
      indices_.push_back(fanLeft);

      while (iss >> token)
      {
        indices_.push_back(fanPivot);
        fanRight = fanLeft;
        indices_.push_back(fanRight);
        fanLeft = std::stoul(token) - 1;
        indices_.push_back(fanLeft);
      }
    }
    else
    {
      // Comments, Do nothing.
    }
  }

  ScaleTo(-1.0f, 1.0f);
  CalculateNormal();
}

Object::Object(MeshData* md) : maxX(-std::numeric_limits<float>::infinity()), minX(std::numeric_limits<float>::infinity()),
                               maxY(-std::numeric_limits<float>::infinity()), minY(std::numeric_limits<float>::infinity()),
                               maxZ(-std::numeric_limits<float>::infinity()), minZ(std::numeric_limits<float>::infinity()),
                               normalMap_(std::map<unsigned int, std::vector<glm::vec3>>())
{
  vertices_ = md->vertices_;
  indices_ = md->indices_;

  //ScaleTo(-1.0f, 1.0f);
  CalculateNormal();
}

Object::~Object()
{

}

void Object::ScaleTo(float lowerBound, float higherBound)
{
  for (unsigned i = 0; i < vertices_.size(); ++i)
  {
    // Normalize x.
    if (maxX - minX == 0)
    {
      vertices_[i].Position.x = 0;
    }
    else
    {
      vertices_[i].Position.x = lowerBound + ((vertices_[i].Position.x - minX) / (maxX - minX)) * (higherBound - lowerBound);
    }
    // Normalize y.
    if (maxY - minY == 0)
    {
      vertices_[i].Position.y = 0;
    }
    else
    {
      vertices_[i].Position.y = lowerBound + ((vertices_[i].Position.y - minY) / (maxY - minY)) * (higherBound - lowerBound);
    }
    // Normalize z.
    if (maxZ - minZ == 0)
    {
      vertices_[i].Position.z = 0;
    }
    else
    {
      vertices_[i].Position.z = lowerBound + ((vertices_[i].Position.z - minZ) / (maxZ - minZ)) * (higherBound - lowerBound);
    }
  }
}

void Object::CalculateNormal()
{
  // For every 3 indices, calculate the face normal.
  for (int i = 0; i < indices_.size(); i += 3)
  {
    int i1 = i + 1;
    int i2 = i + 2;
    unsigned int p = indices_[i];     // pivot vertex index
    unsigned int r = indices_[i1]; // right vertex index
    unsigned int l = indices_[i2]; // left vertex index

    // cross product.
    glm::vec3 tempNormal = glm::normalize(glm::cross(vertices_[r].Position - vertices_[p].Position, vertices_[l].Position - vertices_[p].Position));

    // Check if there exist parallel normal.
    // pivot.
    std::map<unsigned int, std::vector<glm::vec3>>::iterator it = normalMap_.find(p);
    if (it != normalMap_.end())
    {
      if (std::find(it->second.begin(), it->second.end(), tempNormal) == it->second.end())
      {
        it->second.push_back(tempNormal);
      }
    }
    else
    {
      std::vector<glm::vec3> tempList = { tempNormal };
      normalMap_.insert({ p, tempList });
    }
    // right.
    it = normalMap_.find(r);
    if (it != normalMap_.end())
    {
      if (std::find(it->second.begin(), it->second.end(), tempNormal) == it->second.end())
      {
        it->second.push_back(tempNormal);
      }
    }
    else
    {
      std::vector<glm::vec3> tempList = { tempNormal };
      normalMap_.insert({ r, tempList });
    }
    // left.
    it = normalMap_.find(l);
    if (it != normalMap_.end())
    {
      if (std::find(it->second.begin(), it->second.end(), tempNormal) == it->second.end())
      {
        it->second.push_back(tempNormal);
      }
    }
    else
    {
      std::vector<glm::vec3> tempList = { tempNormal };
      normalMap_.insert({ l, tempList });
    }
  }

  // put the adjusted normal into vertices_.
  for (int i = 0; i < vertices_.size(); ++i)
  {
    vertices_[i].Normal = glm::vec3(0.0f, 0.0f, 0.0f); // Default normal.

    std::map<unsigned int, std::vector<glm::vec3>>::iterator it = normalMap_.find(i);
    if (it != normalMap_.end())
    {
      //vertices_[i].Normal = glm::normalize(accumulate(it->second.begin(), it->second.end(), glm::vec3(0.0f, 0.0f, 0.0f)) / (float)it->second.size()); 
      for (glm::vec3 n : it->second)
      {
        vertices_[i].Normal = glm::normalize(vertices_[i].Normal + n);
      }
    }

    vertices_[i].Color = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f); // Set color to default(yellow).
  }
}

std::vector<MeshData::Vertex>& Object::GetVertices()
{
  return vertices_;
}

std::vector<unsigned int>& Object::GetIndices()
{
  return indices_;
}