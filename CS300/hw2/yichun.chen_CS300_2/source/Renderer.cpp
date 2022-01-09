/* Start Header -------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: Renderer.cpp
Purpose: Renderer class.
Language: c++ / Visual Studio compiler 2019
Platform: Visual Studio compiler 2019 / Windows 10
Project: yichun.chen_CS300_2
Author: Yi-Chun Chen / yichun.chen / 180000819
Creation date: 09/28/2020
End Header --------------------------------------------------------*/

#include "Renderer.h"

Renderer::Renderer()
{
  ShaderSetup();

  // create buffers/arrays
  glGenVertexArrays(1, &VAOId_);
  glGenBuffers(1, &VBOId_);
  glGenBuffers(1, &EBOId_);

  glBindVertexArray(VAOId_); // Start record.
  glBindBuffer(GL_ARRAY_BUFFER, VBOId_);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOId_);

  // set the vertex attribute pointers
  // vertex Positions
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(MeshData::Vertex), (void*)offsetof(MeshData::Vertex, Position));
  // vertex texture coords
  //glEnableVertexAttribArray(1);
  //glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(MeshData::Vertex), (void*)offsetof(MeshData::Vertex, TexCoords));
  // vertex color
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(MeshData::Vertex), (void*)offsetof(MeshData::Vertex, Color));
  // vertex normals
  glEnableVertexAttribArray(3);
  glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(MeshData::Vertex), (void*)offsetof(MeshData::Vertex, Normal));
#if 0
  // vertex tangent
  glEnableVertexAttribArray(3);
  glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
  // vertex bitangent
  glEnableVertexAttribArray(4);
  glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));
#endif

  glBindVertexArray(0); // end record.
}

Renderer::~Renderer()
{
  delete diffuse_;
  delete phoneLighting_;

  glDeleteVertexArrays(1, &VAOId_);
  glDeleteBuffers(1, &VBOId_);
  glDeleteBuffers(1, &EBOId_);
}

void Renderer::Clear(const glm::vec4& color)
{
  // Clear frame buffer
  glClearColor(color.r, color.g, color.b, color.a);
  // Clear depth buffer.
  glClearDepth(1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Begin()
{
  tempMD_.type_ = MeshData::Type::ARRAY;
  tempMD_.mode_ = MeshData::Mode::TEXTURE;
  //tempMD_.pTexture_ = nullptr;
  tempMD_.frameWidth = 0.0f;
  tempMD_.frameHeight = 0.0f;
  tempMD_.vertices_.clear();
  tempMD_.indices_.clear();
}

void Renderer::End()
{
  CreateMesh();
}

void Renderer::AppendVertex(MeshData::Vertex vertex)
{
  //vertices_.push_back(vertex);
  tempMD_.vertices_.push_back(vertex);
}

void Renderer::AppendIndex(GLuint index)
{
  //indices_.push_back(index);
  tempMD_.indices_.push_back(index);
}

void Renderer::CreateMesh()
{
  //tempMD_.vertices_ = vertices_;
  //tempMD_.indices_ = indices_;
  if (tempMD_.indices_.size() != 0)
  {
    tempMD_.type_ = MeshData::Type::ELEMENT;
  }
  meshList_.push_back(tempMD_);
}

#if 0
void Renderer::DefineTexture(Texture *pTexture)
{
  tempMD_.pTexture_ = pTexture;

  for (unsigned i = 0; i < textureList_.size(); ++i)
  {
    if (textureList_[i] == pTexture)
    {
      tempMD_.pTexture_->texId = textureList_[i]->texId;
      return;
    }
  }

  glActiveTexture(GL_TEXTURE0);
  glGenTextures(1, &tempMD_.pTexture_->texId);
  glBindTexture(GL_TEXTURE_2D, tempMD_.pTexture_->texId);
  // set the texture wrapping/filtering options (on currently bound texture)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  if (tempMD_.pTexture_->nrChannels == 3) // .jpg
  {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tempMD_.pTexture_->width, tempMD_.pTexture_->height, 0, GL_RGB, GL_UNSIGNED_BYTE, tempMD_.pTexture_->imgHandle);
  }
  else // (meshList_[i].mTexture->GetChannelNumber() == 4) // .png
  {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tempMD_.pTexture_->width, tempMD_.pTexture_->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tempMD_.pTexture_->imgHandle);
  }
  glGenerateMipmap(GL_TEXTURE_2D);

  textureList_.push_back(tempMD_.pTexture_);
}
#endif

void Renderer::AddLine(glm::vec3 start, glm::vec3 end, glm::vec4 color)
{
  MeshData::Vertex s, e;
  s.Position.x = start.x;
  s.Position.y = start.y;
  s.Position.z = start.z;
  s.Color = color;
  e.Position.x = end.x;
  e.Position.y = end.y;
  e.Position.z = end.z;
  e.Color = color;
  AppendVertex(s);
  AppendVertex(e);

  tempMD_.type_ = MeshData::Type::LINE;
  tempMD_.mode_ = MeshData::Mode::COLOR;
  //tempMD_.pTexture_ = nullptr;
  tempMD_.frameWidth = 0.0f;
  tempMD_.frameHeight = 0.0f;
}

void Renderer::AddMesh(MeshData *md)
{
  meshList_.push_back(*md);
}

void Renderer::AddNormal(MeshData* md)
{
  for (int i = 0; i < md->vertices_.size(); ++i)
  {
    Begin();
    AddLine(md->vertices_[i].Position, md->vertices_[i].Position + md->vertices_[i].Normal * 0.2f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    End();
  } 
}

void Renderer::AddFaceNormal(MeshData* md)
{
  for (int i = 0; i < md->indices_.size(); i += 3)
  {
    glm::vec3 middlePoint, pivot, right, left;
    glm::vec3 faceNormal;
    int i1 = i + 1;
    int i2 = i + 2;
    unsigned int p = md->indices_[i];     // pivot vertex index
    unsigned int r = md->indices_[i1]; // right vertex index
    unsigned int l = md->indices_[i2]; // left vertex index
    pivot = md->vertices_[p].Position;
    right = md->vertices_[r].Position;
    left = md->vertices_[l].Position;

    faceNormal = glm::normalize(glm::cross(right - pivot, left - pivot));
    //middlePoint = ((right + left) / 2.0f + pivot) / 2.0f;
    middlePoint = (right + left + pivot) / 3.0f;

    Begin();
    AddLine(middlePoint, middlePoint + faceNormal * 0.2f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    End();
  }
}

// Loop through the mesh list
//   Send all the vertices to the VBO.
//   Send all the indices to the EBO.
//   Create texture buffer and store handle to meshInfo list.
void Renderer::AddBatch()
{
  std::vector<MeshData::Vertex> allVertices;
  std::vector<unsigned int> allIndices;

  // Start record.
  glBindVertexArray(VAOId_);

  for (unsigned i = 0; i < meshList_.size(); ++i)
  {
    MeshData::MeshInfo mi;
    mi.vertOffset = static_cast<GLint>(allVertices.size());
    mi.indexOffset = static_cast<GLint>(allIndices.size());

    mi.type = meshList_[i].type_;
    mi.mode = meshList_[i].mode_;

    // Add indices.
    mi.totalMeshIndices = static_cast<GLuint>(meshList_[i].indices_.size());
    for (unsigned j = 0; j < meshList_[i].indices_.size(); ++j)
    {
      allIndices.push_back(meshList_[i].indices_[j]);
    }

    // Add vertices.
    mi.totalMeshVertices = static_cast<GLuint>(meshList_[i].vertices_.size());
    for (unsigned j = 0; j < meshList_[i].vertices_.size(); ++j)
    {
      allVertices.push_back(meshList_[i].vertices_[j]);
    }
#if 0
    // Store texture id to meshInfo.
    if (meshList_[i].pTexture_)
    {
      mi.texID = meshList_[i].pTexture_->texId;
      // Store channel number into meshInfo.
      mi.nrChannels = meshList_[i].pTexture_->nrChannels;
    }
#endif
    meshInfoList_.push_back(mi);
  }

  // Add to VBO.
  glBindBuffer(GL_ARRAY_BUFFER, VBOId_);
  glBufferData(GL_ARRAY_BUFFER, allVertices.size() * sizeof(MeshData::Vertex), &allVertices[0], GL_STATIC_DRAW);
  // Add to EBO.
  if (allIndices.size() != 0)
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOId_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, allIndices.size() * sizeof(GLuint), &allIndices[0], GL_STATIC_DRAW);
  }

  // End record.
  glBindVertexArray(0);

  meshList_.clear();
}

void Renderer::ClearMesh()
{
  meshInfoList_.clear();
}

void Renderer::SetModelMatrix(const glm::mat4& M)
{
  currentShader_->UseProgram();

  glm::mat4 L = glm::mat4(M[0], M[1], M[2], glm::vec4(0, 0, 0, 1));
  glm::mat4 L_inverseTranspose = glm::transpose(glm::inverse(L));

  glUniformMatrix4fv(currentShader_->GetUniformLocation("model_matrix"), 1, false, &M[0][0]);
  glUniformMatrix4fv(currentShader_->GetUniformLocation("normal_matrix"), 1, false, &L_inverseTranspose[0][0]);

  currentShader_->CloseProgram();
}

void Renderer::SetCamera(const Camera& cam)
{
  currentShader_->UseProgram();

  //glm::vec4 eye_pos = glm::vec4(cam.GetPosition(), 1.0f);

  //glUniformMatrix4fv(uPerspMatrix, 1, false, &projection[0][0]);
  glUniformMatrix4fv(currentShader_->GetUniformLocation("persp_matrix"), 1, false, &cam.GetProjectionMatrix()[0][0]);
  glUniformMatrix4fv(currentShader_->GetUniformLocation("view_matrix"), 1, false, &cam.GetViewMatrix()[0][0]);
  //glUniform4f(uEyePosition, eye_pos.x, eye_pos.y, eye_pos.z, eye_pos.w);

  currentShader_->CloseProgram();
}

void Renderer::SetModelViewMatrix(const glm::mat4& M, const Camera& cam)
{
  if (currentShader_ == phoneLighting_ || currentShader_ == phoneShading_ || currentShader_ == blinnShading_)
  {
    currentShader_->UseProgram();
    glm::mat4 modelViewMatrix = cam.GetViewMatrix() * M;
    glUniformMatrix4fv(currentShader_->GetUniformLocation("modelView_matrix"), 1, false, &modelViewMatrix[0][0]);
    currentShader_->CloseProgram();
  }
}

void Renderer::SetLightSource(LightSource& ls)
{
  if (currentShader_ == phoneLighting_ || currentShader_ == phoneShading_ || currentShader_ == blinnShading_)
  {
    currentShader_->UseProgram();

    int id = ls.GetId();
    glUniform1i(currentShader_->GetUniformLocation("light_on") + id, ls.GetLightOn());
    glUniform4f(currentShader_->GetUniformLocation("light_position") + id, ls.GetPosition().x, ls.GetPosition().y, ls.GetPosition().z, ls.GetPosition().w);
    glUniform3f(currentShader_->GetUniformLocation("ambient") + id, ls.GetAmbient().x, ls.GetAmbient().y, ls.GetAmbient().z);
    glUniform3f(currentShader_->GetUniformLocation("diffuse") + id, ls.GetDiffuse().x, ls.GetDiffuse().y, ls.GetDiffuse().z);
    glUniform3f(currentShader_->GetUniformLocation("specular") + id, ls.GetSpecular().x, ls.GetSpecular().y, ls.GetSpecular().z);
    glUniform1f(currentShader_->GetUniformLocation("shininess") + id, ls.GetShininess());

    currentShader_->CloseProgram();
  }
}

void Renderer::SetShader(Shader::SHADER_TYPE shaderType)
{
  switch (shaderType)
  {
    case Shader::SHADER_TYPE::DIFFUSE:
      currentShader_ = diffuse_;
      break;
    case Shader::SHADER_TYPE::PHONE_LIGHTING:
      currentShader_ = phoneLighting_;
      break;
    case Shader::SHADER_TYPE::PHONE_SHADING:
      currentShader_ = phoneShading_;
      break;
    case Shader::SHADER_TYPE::BLINN_SHADING:
      currentShader_ = blinnShading_;
      break;
  }
}

void Renderer::Render()
{
  currentShader_->UseProgram();

  glBindVertexArray(VAOId_);
  for (unsigned i = 0; i < meshInfoList_.size(); ++i)
  {
    if (meshInfoList_[i].mode == MeshData::Mode::TEXTURE)
    {
      glBindTexture(GL_TEXTURE_2D, meshInfoList_[i].texID);
      glUniform1i(currentShader_->GetUniformLocation("mode"), 0);
    }
    else
    {
      glUniform1i(currentShader_->GetUniformLocation("mode"), 1);
    }

    //if (meshInfoList_[i].totalMeshIndices == 0)
    if (meshInfoList_[i].type == MeshData::Type::ARRAY)
    {
      glDrawArrays(GL_TRIANGLES, meshInfoList_[i].vertOffset, meshInfoList_[i].totalMeshVertices);
    }
    else if (meshInfoList_[i].type == MeshData::Type::ELEMENT)
    {
      glDrawElements(GL_TRIANGLES, meshInfoList_[i].totalMeshIndices, GL_UNSIGNED_INT, reinterpret_cast<const GLvoid*>(meshInfoList_[i].indexOffset));
    }
    else // meshInfoList_[i].type == MeshData::MeshInfo::Type::LINE
    {
      glDrawArrays(GL_LINE_STRIP, meshInfoList_[i].vertOffset, meshInfoList_[i].totalMeshVertices);
    }
  }
  glBindVertexArray(0);

  currentShader_->CloseProgram();
}

void Renderer::ShaderSetup()
{
  // Create shader programs.
  diffuse_ = new Shader("./shader/Shader.vert", "./shader/Shader.frag");
  phoneLighting_ = new Shader("./shader/PhoneLighting.vert", "./shader/PhoneLighting.frag");
  phoneShading_ = new Shader("./shader/PhoneShading.vert", "./shader/PhoneShading.frag");
  blinnShading_ = new Shader("./shader/BlinnShading.vert", "./shader/BlinnShading.frag");

  glEnable(GL_DEPTH_TEST);

  currentShader_ = diffuse_;
}