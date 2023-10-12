#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <R1/Camera.h>
#include <R1/Mesh.h>
#include <GLFW/glfw3.h>

R1::Camera::Camera(GLFWwindow *window)
{
  this->window = window;
  std::cout << "Camera::Camera()" << std::endl;
  Mesh *cameraMesh = new Mesh();
  cameraMesh->setPosition(glm::vec3(0, 0, 5));
  cameraMesh->setRotation(glm::vec3(0, 0, 90));
  cameraMesh->setIsCamera(true);
  this->mesh = cameraMesh;

  cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
  cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
  view = glm::lookAt(mesh->getPosition(), mesh->getPosition() + cameraFront, cameraUp);
  projection = glm::perspective(glm::radians(fov), (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);

  this->mesh->setOnPositionChangeCallback([this](glm::vec3 newPosition)
                                          { this->updateMatrix(); });

  this->mesh->setOnRotationChangeCallback([this](glm::vec3 newRotation)
                                          { this->updateMatrix(); });

  this->mesh->setOnScaleChangeCallback([this](glm::vec3 newScale)
                                       { this->updateMatrix(); });
}

void R1::Camera::setScreenSize(int screenWidth, int screenHeight)
{
  std::cout << "Camera::setScreenSize()" << screenWidth << "x" << screenHeight << std::endl;
  if (screenWidth == 0 || screenHeight == 0)
  {
    std::cout << "Camera::setScreenSize() screenWidth or screenHeight is 0" << std::endl;
    return;
  }
  this->screenWidth = screenWidth;
  this->screenHeight = screenHeight;
  updateMatrix();
}

void R1::Camera::updateMatrix()
{
  updateProjectionMatrix();
  updateViewMatrix();
}

void R1::Camera::updateProjectionMatrix()
{
  projection = glm::perspective(glm::radians(fov), (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);
}

void R1::Camera::updateViewMatrix()
{
  view = glm::lookAt(mesh->getPosition(), mesh->getPosition() + cameraFront, cameraUp);
}

bool R1::Camera::getIsMouseVisible()
{
  return isMouseVisible;
}

void R1::Camera::setIsMouseVisible(bool visible)
{
  isMouseVisible = visible;
}

void R1::Camera::setFov(float fov)
{
  this->fov = fov;
  updateProjectionMatrix();
}

float R1::Camera::getFov()
{
  return fov;
}

void R1::Camera::handleInput(float deltaTime)
{
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
  {
    if (isMouseVisible)
    {
      return;
    }
    mesh->setPosition(mesh->getPosition() + (speed * deltaTime) * cameraFront);
  }

  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
  {
    if (isMouseVisible)
    {
      return;
    }
    mesh->setPosition(mesh->getPosition() - (speed * deltaTime) * cameraFront);
  }

  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
  {
    if (isMouseVisible)
    {
      return;
    }
    mesh->setPosition(mesh->getPosition() - glm::normalize(glm::cross(cameraFront, cameraUp)) * (speed * deltaTime));
  }

  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
  {
    if (isMouseVisible)
    {
      return;
    }
    mesh->setPosition(mesh->getPosition() + glm::normalize(glm::cross(cameraFront, cameraUp)) * (speed * deltaTime));
  }

  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
  {
    glfwSetWindowShouldClose(window, GLFW_TRUE);
  }

  if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)
  {
    if (glfwGetTime() - lastTimeMouseVisible < 0.3f)
      return;

    lastTimeMouseVisible = glfwGetTime();

    isMouseVisible = !isMouseVisible;
    glfwSetInputMode(window, GLFW_CURSOR, isMouseVisible ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
  }
}

void R1::Camera::handleMouse(GLdouble xpos, GLdouble ypos)
{

  if (isMouseVisible)
  {
    isFirstMouse = true;
    return;
  }

  if (isFirstMouse)
  {
    lastX = xpos;
    lastY = ypos;
    isFirstMouse = false;
  }

  float xoffset = xpos - lastX;
  float yoffset = lastY - ypos;
  lastX = xpos;
  lastY = ypos;

  xoffset *= sensitivity;
  yoffset *= sensitivity;

  yaw += xoffset;
  pitch += yoffset;

  if (pitch > 89.0f)
    pitch = 89.0f;
  if (pitch < -89.0f)
    pitch = -89.0f;

  if (yaw > 360.0f)
    yaw = 0.0f;
  if (yaw < 0.0f)
    yaw = 360.0f;

  glm::vec3 direction;
  direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
  direction.y = sin(glm::radians(pitch));
  direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

  cameraFront = glm::normalize(direction);
  mesh->setRotation(glm::vec3(pitch, yaw, 90.0f - yaw));

  updateMatrix();
}

void R1::Camera::handleScroll(GLdouble yoffset)
{
  if (isMouseVisible)
    return;

  if (fov >= minFov && fov <= maxFov)
    fov -= yoffset * 1.5f;
  if (fov <= minFov)
    fov = minFov;
  if (fov >= maxFov)
    fov = maxFov;

  updateMatrix();
}

glm::mat4 R1::Camera::getViewMatrix()
{
  return view;
}

glm::mat4 R1::Camera::getProjectionMatrix()
{
  return projection;
}

R1::Mesh *R1::Camera::getMesh()
{
  return mesh;
}

void R1::Camera::setIsActiveCamera(bool isActiveCamera)
{
  this->isActiveCamera = isActiveCamera;

  updateMatrix();
}

bool R1::Camera::getIsActiveCamera()
{
  return isActiveCamera;
}

void R1::Camera::setIsCameraDeleted(bool deleted)
{
  isCameraDeleted = deleted;
}

bool R1::Camera::getIsCameraDeleted()
{
  return isCameraDeleted;
}

void R1::Camera::cleanup()
{
  std::cout << "Camera::cleanup()" << std::endl;
}