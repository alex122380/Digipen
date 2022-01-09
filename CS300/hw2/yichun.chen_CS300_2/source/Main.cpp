/* Start Header -------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: Main.cpp
Purpose: Setup the scene.
Language: c++ / Visual Studio compiler 2019
Platform: Visual Studio compiler 2019 / Windows 10
Project: yichun.chen_CS300_2
Author: Yi-Chun Chen / yichun.chen / 180000819
Creation date: 09/28/2020
End Header --------------------------------------------------------*/

#include <Windows.h>
#include "WindowSystem.h"
#include "Renderer.h"
#include "Object.h"
#include <chrono>
#include "ImGuiManager.h"
#include "LightSource.h"

static int modelNumber = 0;
static const float timeUnit = 0.01f;
static float objectTheta = 0.0f;
static float orbitRadius = 3.0f;
static const float ad = (2 * glm::pi<float>()) / 16; // Angular distance between spheres.
static float orbitTheta[16] = { 
  0, ad, 2 * ad, 3 * ad, 4 * ad, 5 * ad, 6 * ad, 7 * ad, 8 * ad, 9 * ad,
  10 * ad, 11 * ad, 12 * ad, 13 * ad, 14 * ad, 15 * ad
};

WindowSystem* pWindowSystem = new WindowSystem("CS300 Assignment2", 1280, 720);
Renderer* pRenderer = new Renderer();
ImGuiManager* pImGuiManager = new ImGuiManager(pWindowSystem->GetWindow());

// MeshData.
MeshData* pMeshDataObject;
MeshData* pMeshDataSphere;
MeshData* pMeshDataFloor;

// Object transformations.
glm::mat4 tObject;
glm::mat4 tSphere[16];
glm::mat4 tOrbit;
glm::mat4 tFloor;

// Light sources.
LightSource* lightSource[16];

void LoadScene();
void UpdateScene();
void RenderScene();
float GetFixedDeltaTime(std::chrono::steady_clock::time_point& current);
MeshData *CreateSphere(float radius, int numDivisions);
MeshData *CreateFloor();

int main()
{
  auto currentTime = std::chrono::steady_clock::now(); // Time passed since startup.
  float accumulator = timeUnit; // Time passed since last update.

  LoadScene();

  while (!pWindowSystem->WindowShouldClose())
  {
    //get time since last tick
    const float delta = GetFixedDeltaTime(currentTime);

    // Input.
    pWindowSystem->ProcessInput();

    // Adjust frame rate.
    accumulator += delta;
    while (accumulator >= timeUnit)
    {
      UpdateScene();

      accumulator -= timeUnit;
    }

    // Render.
    pRenderer->Clear(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));
    RenderScene();
    pImGuiManager->Update();

    pWindowSystem->SwapBuffers();
    pWindowSystem->PollEvents();
  }

  return 0;
}

void LoadScene()
{
  Object* pObject = new Object("sphere.obj");
  pMeshDataObject = new MeshData(MeshData::Type::ELEMENT, MeshData::Mode::COLOR, pObject->GetVertices(), pObject->GetIndices());
  delete pObject;

  // Procedurally generate sphere mesh.
  pMeshDataSphere = CreateSphere(1.0f, 40);
  pObject = new Object(pMeshDataSphere);
  delete pMeshDataSphere;
  pMeshDataSphere = new MeshData(MeshData::Type::ELEMENT, MeshData::Mode::COLOR, pObject->GetVertices(), pObject->GetIndices());
  delete pObject;

  // Generate floor.
  pMeshDataFloor = CreateFloor();

  // Create light sources.
  for (int i = 0; i < 16; ++i)
  {
    lightSource[i] = new LightSource(
      i,
      false,
      glm::vec4(pWindowSystem->cam->GetPosition(), 1.0f),
      glm::vec3(0.0f, 0.0f, 0.0f),
      glm::vec3(1.0f, 1.0f, 0.0f),
      glm::vec3(1.0f, 1.0f, 1.0f),
      30.0f
    );
  }

  lightSource[0]->SetLightOn(true);
}

void UpdateScene()
{
  // Set Obj transformation.
  // I * T
  // I * T * R
  // I * T * R * S
  tObject = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
  tObject = glm::rotate(tObject, glm::radians(objectTheta), glm::vec3(1.0f, 0.0f, 0.0f));
  objectTheta += (2 * glm::pi<float>()) / 36;
  tObject = glm::scale(tObject, glm::vec3(1.0f, 1.0f, 1.0f));

  // Set spheres transformation.
  for (int i = 0; i < 16; ++i)
  {
    float x = orbitRadius * glm::cos(orbitTheta[i]);
    float z = orbitRadius * glm::sin(orbitTheta[i]);
    orbitTheta[i] += (2 * glm::pi<float>()) / 360;
    tSphere[i] = glm::translate(glm::mat4(1.0f), glm::vec3(x, 0.0f, z));
    tSphere[i] = glm::rotate(tSphere[i], glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    tSphere[i] = glm::scale(tSphere[i], glm::vec3(0.1f, 0.1f, 0.1f));

    lightSource[i]->SetPosition(glm::vec4(x, 0.0f, z, 1.0f));
  }

  // Set orbit transformation.
  tOrbit = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
  tOrbit = glm::rotate(tOrbit, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
  tOrbit = glm::scale(tOrbit, glm::vec3(orbitRadius, orbitRadius, orbitRadius));

  // Set floor transformation.
  tFloor = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -2.0f, 0.0f));
  tFloor = glm::rotate(tFloor, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
  tFloor = glm::scale(tFloor, glm::vec3(10.0f, 10.0f, 10.0f));

  // Set Camera.
  // -------------------------------------------------------------------------
  pRenderer->SetCamera(*pWindowSystem->cam);

  for (int i = 0; i < 16; ++i)
  {
    pRenderer->SetLightSource(*lightSource[i]);
  }
}

void RenderScene()
{
  int shaderNumber = pImGuiManager->GetCurrentShader();
  switch (shaderNumber)
  {
    case 0:
      pRenderer->SetShader(Shader::SHADER_TYPE::DIFFUSE);
      break;
    case 1:
      pRenderer->SetShader(Shader::SHADER_TYPE::PHONE_LIGHTING);
      break;
    case 2:
      pRenderer->SetShader(Shader::SHADER_TYPE::PHONE_SHADING);
      break;
    case 3:
      pRenderer->SetShader(Shader::SHADER_TYPE::BLINN_SHADING);
      break;
  }

  if (pImGuiManager->GetCurrentModel() != modelNumber)
  {
    modelNumber = pImGuiManager->GetCurrentModel();
    Object* pObject = new Object(pImGuiManager->GetCurrentModelName());
    pMeshDataObject = new MeshData(MeshData::Type::ELEMENT, MeshData::Mode::COLOR, pObject->GetVertices(), pObject->GetIndices());
    delete pObject;
  }

  // Render object.
  pRenderer->AddMesh(pMeshDataObject);
  int normalDisplay = pImGuiManager->GetNormalDisplay();
  if (normalDisplay == 0)
  {
    // Add nothing.
  }
  else if (normalDisplay == 1)
  {
    pRenderer->AddNormal(pMeshDataObject);
  }
  else // normalDisplay == 2
  {
    pRenderer->AddFaceNormal(pMeshDataObject);
  }
  pRenderer->AddBatch();
  pRenderer->SetModelMatrix(tObject);
  pRenderer->SetModelViewMatrix(tObject, *pWindowSystem->cam);
  pRenderer->Render();
  pRenderer->ClearMesh();

  // Render spheres.
  pRenderer->AddMesh(pMeshDataSphere);
  pRenderer->AddBatch();
  for (int i = 0; i < 16; ++i)
  {
    pRenderer->SetModelMatrix(tSphere[i]);
    pRenderer->SetModelViewMatrix(tSphere[i], *pWindowSystem->cam);
    pRenderer->Render();
  }
  pRenderer->ClearMesh();

  // Render orbit.
  float startTheta = 0.0f;
  float endTheta = startTheta + (2 * glm::pi<float>()) / 360;
  for (int i = 0; i < 360; ++i)
  {
    float startX = glm::cos(startTheta);
    float startZ = glm::sin(startTheta);
    float endX = glm::cos(endTheta);
    float endZ = glm::sin(endTheta);
    pRenderer->Begin();
    pRenderer->AddLine(glm::vec3(startX, 0.0f, startZ), glm::vec3(endX, 0.0f, endZ), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
    pRenderer->End();

    startTheta = endTheta;
    endTheta += (2 * glm::pi<float>()) / 360;
  }
  pRenderer->AddBatch();
  pRenderer->SetModelMatrix(tOrbit);
  pRenderer->SetModelViewMatrix(tOrbit, *pWindowSystem->cam);
  pRenderer->Render();
  pRenderer->ClearMesh();

  // Render floor.
  pRenderer->AddMesh(pMeshDataFloor);
  pRenderer->AddBatch();
  pRenderer->SetModelMatrix(tFloor);
  pRenderer->SetModelViewMatrix(tFloor, *pWindowSystem->cam);
  pRenderer->Render();
  pRenderer->ClearMesh();
}

float GetFixedDeltaTime(std::chrono::steady_clock::time_point& current)
{
  auto newTime = std::chrono::steady_clock::now();
  auto duration = std::chrono::duration<float>(newTime - current);
  float frameTime = duration.count();
  current = newTime;

  if (frameTime > 0.25f)
  {
    frameTime = 0.25f;
  }

  return frameTime;
}

MeshData* CreateSphere(float radius, int numDivisions)
{
  MeshData* md = new MeshData();
  md->type_ = MeshData::Type::ELEMENT;
  md->mode_ = MeshData::Mode::COLOR;

  float theta = 0.0f;
  float deltaTheta = 180.0f / numDivisions;
  float phi = 0.0f;
  float deltaPhi = 360.0f / numDivisions;

  // Vertices.
  // ---------------------------------------------------------------------------------------
  MeshData::Vertex frontPole;
  frontPole.Position = glm::vec3(0.0f, 0.0f, radius);
  md->vertices_.push_back(frontPole);
  for (int i = 0; i < numDivisions - 1; ++i)
  {
    theta += deltaTheta;
    for (int j = 0; j < numDivisions; ++j)
    {
      phi += deltaPhi;
      MeshData::Vertex v;
      v.Position.x = radius * glm::sin(glm::radians(theta)) * glm::cos(glm::radians(phi));
      v.Position.y = radius * glm::sin(glm::radians(theta)) * glm::sin(glm::radians(phi));
      v.Position.z = radius * glm::cos(glm::radians(theta));
      md->vertices_.push_back(v);
    }
  }
  MeshData::Vertex backPole;
  backPole.Position = glm::vec3(0.0f, 0.0f, -radius);
  md->vertices_.push_back(backPole);

  // Indices.
  // ------------------------------------------------------------------------------------------
  // Front cap.
  for (int i = 1; i <= numDivisions; ++i)
  {
    md->indices_.push_back(0);
    md->indices_.push_back(i);
    if (i == numDivisions)
    {
      md->indices_.push_back(1);
    }
    else
    {
      md->indices_.push_back(i + 1);
    }
  }
  // Middle belts.
  for (int i = 0; i < numDivisions - 2; ++i)
  {
    for (int j = 1; j <= numDivisions; ++j)
    {
      // First triangle.
      md->indices_.push_back(j + numDivisions * i);
      md->indices_.push_back(j + numDivisions * (i + 1));
      int k;
      if (j == numDivisions)
      {
        k = 1;
      }
      else
      {
        k = j + 1;
      }
      md->indices_.push_back(k + numDivisions * i);
      // Second triangle.
      md->indices_.push_back(k + numDivisions * i);
      md->indices_.push_back(j + numDivisions * (i + 1));
      md->indices_.push_back(k + numDivisions * (i + 1));
    }
  }
  // Back cap.
  for (int i = 1; i <= numDivisions; ++i)
  {
    md->indices_.push_back((numDivisions - 2) * numDivisions + i);
    md->indices_.push_back((unsigned int)md->vertices_.size() - 1);
    int k;
    if (i == numDivisions)
    {
      k = 1;
    }
    else
    {
      k = i + 1;
    }
    md->indices_.push_back((numDivisions - 2) * numDivisions + k);
  }

  return md;
}

MeshData *CreateFloor()
{
  // Manually create mesh data (quad).
  // Should be read from file in the future.
  // -------------------------------------------------------------------------
  // 3-----0
  // |     |
  // 2-----1
  // Vertices.
  std::vector<MeshData::Vertex> vertices;
  // position.
  glm::vec3 p0 = glm::vec3( 0.5f, 0.0f,  0.5f); // top right
  glm::vec3 p1 = glm::vec3( 0.5f, 0.0f, -0.5f); // bottom right
  glm::vec3 p2 = glm::vec3(-0.5f, 0.0f, -0.5f); // bottom left
  glm::vec3 p3 = glm::vec3(-0.5f, 0.0f,  0.5f); // top left
  // normal.
  glm::vec3 n0 = glm::vec3( 0.0f,  1.0f,  0.0f); // top right
  glm::vec3 n1 = glm::vec3( 0.0f,  1.0f,  0.0f); // bottom right
  glm::vec3 n2 = glm::vec3( 0.0f,  1.0f,  0.0f); // bottom left
  glm::vec3 n3 = glm::vec3( 0.0f,  1.0f,  0.0f); // top left
  // texture coordinate.
  glm::vec2 t0 = glm::vec2(1.0f, 0.0f); // top right
  glm::vec2 t1 = glm::vec2(1.0f, 1.0f); // bottom right
  glm::vec2 t2 = glm::vec2(0.0f, 1.0f); // bottom left
  glm::vec2 t3 = glm::vec2(0.0f, 0.0f); // top left
  // color.
  glm::vec4 c0 = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f); // top right
  glm::vec4 c1 = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f); // bottom right
  glm::vec4 c2 = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f); // bottom left
  glm::vec4 c3 = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f); // top left

  MeshData::Vertex v0 = { p0, t0, c0, n0 },
                   v1 = { p1, t1, c1, n1 },
                   v2 = { p2, t2, c2, n2 },
                   v3 = { p3, t3, c3, n3 };
  vertices.push_back(v0);
  vertices.push_back(v1);
  vertices.push_back(v2);
  vertices.push_back(v3);
  // Indices.
  std::vector<unsigned int> indices = { 
    0, 1, 2, // First triangle.
    0, 2, 3  // Second triangle.
  };

  return new MeshData(MeshData::Type::ELEMENT, MeshData::Mode::TEXTURE, vertices, indices, 1.0f, 1.0f);
}