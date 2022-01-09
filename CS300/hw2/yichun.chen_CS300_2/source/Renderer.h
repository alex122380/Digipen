/* Start Header -------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: Renderer.h
Purpose: Renderer class.
Language: c++ / Visual Studio compiler 2019
Platform: Visual Studio compiler 2019 / Windows 10
Project: yichun.chen_CS300_2
Author: Yi-Chun Chen / yichun.chen / 180000819
Creation date: 09/28/2020
End Header --------------------------------------------------------*/

#pragma once

#ifndef RENDERER_H
#define RENDERER_H

#include "MeshData.h"
#include <glad/glad.h>
#include <vector>
//#include "Texture.h"
#include "Shader.h"
#include "Camera.h"
#include "LightSource.h"

class Renderer
{
  public:
    Renderer();
    ~Renderer();
    static void Clear(const glm::vec4& color);
    void Begin();
    void End();
    void AppendVertex(MeshData::Vertex vertex);
    void AppendIndex(GLuint index);
    void CreateMesh();
    void AddLine(glm::vec3 start, glm::vec3 end, glm::vec4 color);
    void AddMesh(MeshData *md);
    void AddNormal(MeshData* md);
    void AddFaceNormal(MeshData* md);
    void AddBatch();
    void ClearMesh();
    // Shader variables related.
    void SetModelMatrix(const glm::mat4& M);
    void SetCamera(const Camera& cam); // Set view and projection matrix.
    void SetModelViewMatrix(const glm::mat4& M, const Camera& cam);
    void SetLightSource(LightSource& ls);
    void SetShader(Shader::SHADER_TYPE shaderType);
    void Render();

  private:
    void ShaderSetup();

    // Shader related.
    Shader* diffuse_;
    Shader* phoneLighting_;
    Shader* phoneShading_;
    Shader* blinnShading_;
    Shader* currentShader_;
    

    // OpenGL buffers.
    GLuint VAOId_; 
    GLuint VBOId_; 
    GLuint EBOId_; 
    MeshData tempMD_;
    std::vector<MeshData> meshList_;
    std::vector<MeshData::MeshInfo> meshInfoList_;
    //std::vector<Texture *> textureList_;
};

#endif