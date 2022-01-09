/* Start Header -------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: Camera.cpp
Purpose: Setup the Camera (view matrix, and projection matrix).
Language: c++ / Visual Studio compiler 2019
Platform: Visual Studio compiler 2019 / Windows 10
Project: yichun.chen_CS300_1
Author: Yi-Chun Chen / yichun.chen / 180000819
Creation date: 09/28/2020
End Header --------------------------------------------------------*/

// Reference:
// https://learnopengl.com/code_viewer_gh.php?code=includes/learnopengl/camera.h
//

#include "Camera.h"
#include "WindowSystem.h"

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float FOV = 90.0f;

Camera::Camera(const glm::vec3& position, const glm::vec3& target, const glm::vec3& worldUp, float fov, float aspect, float N, float F) 
              : mPosition(position), mWorldUp(worldUp), mYaw(YAW), mPitch(), mMovementSpeed(SPEED), mMouseSensitivity(SENSITIVITY), mFov(fov), mNearDistance(N), mFarDistance(F)
{
  mFront = glm::normalize(target - mPosition);

  mRight = glm::normalize(glm::cross(mFront, mWorldUp));
  mUp = glm::cross(mRight, mFront);

  mVpDistance = mNearDistance; //Use OpenGL convention.

  mVpWidth = tan(glm::radians(mFov) / 2) * 2 * mVpDistance;
  mVpHeight = mVpWidth / aspect;
}

Camera::Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : mFront(glm::vec3(0.0f, 0.0f, -1.0f)), mMovementSpeed(SPEED), mMouseSensitivity(SENSITIVITY), mFov(FOV)
{
  mPosition = position;
  mWorldUp = worldUp;
  mYaw = yaw;
  mPitch = pitch;
  updateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : mFront(glm::vec3(0.0f, 0.0f, -1.0f)), mMovementSpeed(SPEED), mMouseSensitivity(SENSITIVITY), mFov(FOV)
{
  mPosition = glm::vec3(posX, posY, posZ);
  mWorldUp = glm::vec3(upX, upY, upZ);
  mYaw = yaw;
  mPitch = pitch;
  updateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix() const
{
  return glm::lookAt(mPosition, mPosition + mFront, mUp);
}

glm::mat4 Camera::GetProjectionMatrix() const
{
#if 0
  //                                          left,       right,        bottom,        top,          near,          far
  glm::mat4 projection = glm::ortho(-(1280.0f / 2), 1280.0f / 2, -(720.0f / 2), 720.0f / 2, mNearDistance, mFarDistance);
#else
  //                                                     fov,                                                         aspect ratio,          near,          far
  //glm::mat4 projection = glm::perspective(glm::radians(mFov), (float)pWindowSystem->GetWidth() / (float)pWindowSystem->GetHeight(), mNearDistance, mFarDistance);
  glm::mat4 projection = glm::perspective(glm::radians(mFov), 1280.0f / 720.0f, mNearDistance, mFarDistance);
#endif

  return projection;
}

void Camera::updateCameraVectors()
{
  // calculate the new Front vector
  glm::vec3 front;
  front.x = cos(glm::radians(mYaw)) * cos(glm::radians(mPitch));
  front.y = sin(glm::radians(mPitch));
  front.z = sin(glm::radians(mYaw)) * cos(glm::radians(mPitch));
  mFront = glm::normalize(front);
  // also re-calculate the Right and Up vector
  mRight = glm::normalize(glm::cross(mFront, mWorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
  mUp = glm::normalize(glm::cross(mRight, mFront));
}