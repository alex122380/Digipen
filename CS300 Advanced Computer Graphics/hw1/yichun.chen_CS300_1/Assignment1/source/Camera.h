/* Start Header -------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: Camera.h
Purpose: Setup the Camera (view matrix, and projection matrix).
Language: c++ / Visual Studio compiler 2019
Platform: Visual Studio compiler 2019 / Windows 10
Project: yichun.chen_CS300_1
Author: Yi-Chun Chen / yichun.chen / 180000819
Creation date: 09/28/2020
End Header --------------------------------------------------------*/

#pragma once

// Reference:
// https://learnopengl.com/code_viewer_gh.php?code=includes/learnopengl/camera.h
//

#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera
{
  public:
    Camera(const glm::vec3& position, const glm::vec3& target, const glm::vec3& worldUp, float fov, float aspect, float N, float F);
    // constructor with vectors
    Camera(glm::vec3 position, glm::vec3 worldUp, float yaw, float pitch);
    // constructor with scalar values
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);
    // returns the view matrix calculated using Euler Angles and the LookAt Matrix
    glm::mat4 GetViewMatrix() const;
    glm::mat4 GetProjectionMatrix() const;
    glm::vec3 GetPosition() const { return mPosition; }
    //glm::vec3 GetFrontVector() { return mFront; }
    //glm::vec3 GetUpVector() { return mUp; }
    //glm::vec3 GetRightVector() { return mRight; }
    float GetFov() const { return mFov; }

#if 0
    // processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    void ProcessKeyboard(Camera_Movement direction, float deltaTime)
    {
      float velocity = MovementSpeed * deltaTime;
      if (direction == FORWARD)
          Position += Front * velocity;
      if (direction == BACKWARD)
          Position -= Front * velocity;
      if (direction == LEFT)
          Position -= Right * velocity;
      if (direction == RIGHT)
          Position += Right * velocity;
    }

    // processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
    {
      xoffset *= MouseSensitivity;
      yoffset *= MouseSensitivity;

      Yaw   += xoffset;
      Pitch += yoffset;

      // make sure that when pitch is out of bounds, screen doesn't get flipped
      if (constrainPitch)
      {
          if (Pitch > 89.0f)
              Pitch = 89.0f;
          if (Pitch < -89.0f)
              Pitch = -89.0f;
      }

      // update Front, Right and Up Vectors using the updated Euler angles
      updateCameraVectors();
    }

    // processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    void ProcessMouseScroll(float yoffset)
    {
      Zoom -= (float)yoffset;
      if (Zoom < 1.0f)
          Zoom = 1.0f;
      if (Zoom > 45.0f)
          Zoom = 45.0f; 
    }
#endif

  //private:
    // camera Attributes
    glm::vec3 mPosition;
    glm::vec3 mFront;
    glm::vec3 mUp;
    glm::vec3 mRight;
    glm::vec3 mWorldUp;

    // euler Angles
    float mYaw;
    float mPitch;
    // camera options
    float mMovementSpeed;
    float mMouseSensitivity;
    float mFov;
    float mNearDistance;
    float mFarDistance;
    float mVpDistance;
    float mVpWidth;
    float mVpHeight;
    // calculates the front vector from the Camera's (updated) Euler Angles
    void updateCameraVectors();
};
#endif