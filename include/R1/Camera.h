#ifndef CAMERA_H
#define CAMERA_H
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <R1/Mesh.h>

namespace R1
{
  class Mesh;
}

namespace R1
{
  class Camera
  {
  public:
    Camera(GLFWwindow *window);
    void cleanup();
    R1::Mesh *getMesh();
    void setWindow(GLFWwindow *window);
    void setScreenSize(int screenWidth, int screenHeight);
    void setFov(float fov);
    void setIsActiveCamera(bool active);
    void setIsMouseVisible(bool visible);
    void setIsCameraDeleted(bool deleted);
    void updateViewMatrix();
    void updateProjectionMatrix();
    void updateMatrix();
    void handleMouse(GLdouble xpos, GLdouble ypos);
    void handleInput(float deltaTime);
    void handleScroll(double yoffset);
    bool getIsActiveCamera();
    bool getIsMouseVisible();
    bool getIsCameraDeleted();
    float getFov();
    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix();

  private:
    R1::Mesh *mesh;
    GLFWwindow *window;
    float lastX;
    float lastY;
    int screenWidth = 800;
    int screenHeight = 600;
    glm::mat4 view;
    glm::mat4 projection;
    glm::vec3 cameraUp;
    glm::vec3 cameraFront;
    float lastTimeMouseVisible = 0.0f;
    float fov = 80.0f;
    float minFov = 1.0f;
    float maxFov = 120.0f;
    float speed = 2.5f;
    float sensitivity = 0.1f;
    float yaw = 0.0f;
    float pitch = 0.0f;
    bool isFirstMouse = true;
    bool isMouseVisible = false;
    bool isActiveCamera = false;
    bool isCameraDeleted = false;
  };
};

#endif