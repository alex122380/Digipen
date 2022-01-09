/* Start Header -------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: Main.cpp
Purpose: Setup the scene.
Language: c++ / Visual Studio compiler 2019
Platform: Visual Studio compiler 2019 / Windows 10
Project: yichun.chen_CS300_1
Author: Yi-Chun Chen / yichun.chen / 180000819
Creation date: 09/28/2020
End Header --------------------------------------------------------*/

#include <Windows.h>
#include "WindowSystem.h"
#include "Renderer.h"
#include "Object.h"
#include <chrono>
#include "ImGuiManager.h"

static int modelNumber = 0;
static const float timeUnit = 0.01f;
static float objectTheta = 0.0f;
static float orbitRadius = 3.0f;
static const float ad = (2 * glm::pi<float>()) / 8; // Angular distance between spheres.
static float orbitTheta[8] = { 0, ad, 2 * ad, 3 * ad, 4 * ad, 5 * ad, 6 * ad, 7 * ad };

WindowSystem* pWindowSystem = new WindowSystem("CS300 Assignment1", 1280, 720);
Renderer* pRenderer = new Renderer();
ImGuiManager* pImGuiManager = new ImGuiManager(pWindowSystem->GetWindow());

// MeshData.
MeshData* pMeshDataObject;
MeshData* pMeshDataSphere;

// Object transformations.
glm::mat4 tObject;
glm::mat4 tSphere[8];
glm::mat4 tOrbit;

void LoadScene();
void UpdateScene();
void RenderScene(int normalDisplay);
float GetFixedDeltaTime(std::chrono::steady_clock::time_point& current);
MeshData* CreateSphere(float radius, int numDivisions);

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
    RenderScene(pImGuiManager->GetNormalDisplay());
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
  for (int i = 0; i < 8; ++i)
  {
    float x = orbitRadius * glm::cos(orbitTheta[i]);
    float z = orbitRadius * glm::sin(orbitTheta[i]);
    orbitTheta[i] += (2 * glm::pi<float>()) / 360;
    tSphere[i] = glm::translate(glm::mat4(1.0f), glm::vec3(x, 0.0f, z));
    tSphere[i] = glm::rotate(tSphere[i], glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    tSphere[i] = glm::scale(tSphere[i], glm::vec3(0.1f, 0.1f, 0.1f));
  }

  // Set orbit transformation.
  tOrbit = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
  tOrbit = glm::rotate(tOrbit, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
  tOrbit = glm::scale(tOrbit, glm::vec3(orbitRadius, orbitRadius, orbitRadius));

  // Set Camera.
  // -------------------------------------------------------------------------
  pRenderer->SetCamera(*pWindowSystem->cam);
}

void RenderScene(int normalDisplay)
{
  if (pImGuiManager->GetCurrentModel() != modelNumber)
  {
    modelNumber = pImGuiManager->GetCurrentModel();
    Object* pObject = new Object(pImGuiManager->GetCurrentModelName());
    pMeshDataObject = new MeshData(MeshData::Type::ELEMENT, MeshData::Mode::COLOR, pObject->GetVertices(), pObject->GetIndices());
    delete pObject;
  }

  // Render object.
  pRenderer->AddMesh(pMeshDataObject);
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
  pRenderer->Render();
  pRenderer->ClearMesh();

  // Render spheres.
  pRenderer->AddMesh(pMeshDataSphere);
  pRenderer->AddBatch();
  for (int i = 0; i < 8; ++i)
  {
    pRenderer->SetModelMatrix(tSphere[i]);
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