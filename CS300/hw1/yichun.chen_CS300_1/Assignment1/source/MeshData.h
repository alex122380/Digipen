/* Start Header -------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: MeshData.h
Purpose: struct for mesh data.
Language: c++ / Visual Studio compiler 2019
Platform: Visual Studio compiler 2019 / Windows 10
Project: yichun.chen_CS300_1
Author: Yi-Chun Chen / yichun.chen / 180000819
Creation date: 09/28/2020
End Header --------------------------------------------------------*/

#pragma once

#ifndef MESHDATA_H
#define MESHDATA_H

#include <glm/glm.hpp>
#include <vector>
#include <string>
//#include <stb_image.h>
//#include "Texture.h"
#include <glad/glad.h>

struct MeshData
{
  enum class Type { ARRAY, ELEMENT, LINE };
  enum class Mode { TEXTURE, COLOR };

  struct Vertex
  {
    // position
    glm::vec3 Position;
    // texCoords
    glm::vec2 TexCoords;
    // color
    glm::vec4 Color;
    // normal
    glm::vec3 Normal;
    // tangent
    //glm::vec3 Tangent;
    // bitangent
    //glm::vec3 Bitangent;
  };

  struct MeshInfo
  {
    MeshInfo() : type(Type::ARRAY), mode(Mode::TEXTURE), texID(0), totalMeshVertices(0), totalMeshIndices(0), vertOffset(0), indexOffset(0), nrChannels(0){}

    Type type;
    Mode mode;
    GLuint texID;
    GLuint totalMeshVertices;
    GLuint totalMeshIndices;
    GLint vertOffset;
    GLuint indexOffset;
    int nrChannels;
  };

  MeshData() : type_(Type::ARRAY), mode_(Mode::TEXTURE), frameWidth(0.0f), frameHeight(0.0f) {}
  MeshData(Type type, Mode mode, std::vector<Vertex> vertices, std::vector<unsigned int> indices) : type_(type), mode_(mode), vertices_(vertices), indices_(indices), frameWidth(0.0f), frameHeight(0.0f) {}
  MeshData(Type type, Mode mode, std::vector<Vertex> vertices, std::vector<unsigned int> indices, float fw, float fh) : type_(type), mode_(mode), vertices_(vertices), indices_(indices), frameWidth(fw), frameHeight(fh) {}

  Type type_;
  Mode mode_;
  std::vector<Vertex> vertices_;
  std::vector<unsigned int> indices_;
  //Texture *pTexture_;
  float frameWidth, frameHeight;
};

#endif