#ifndef SCENE_H
#define SCENE_h
#include <GLFW/glfw3.h>
#include <iostream>
#include <R1/Camera.h>
#include <R1/Mesh.h>
#include <R1/Light.h>
#include <R1/Imgui.h>
#include <R1/Line.h>

namespace R1
{
  class Scene
  {
  public:
    Scene(GLFWwindow *window);
    void setup();
    void cleanup();
    Camera *getCamera();
    void setScreenSize(int screenWidth, int screenHeight);
    void loop();
    int screenWidth = 800;
    int screenHeight = 600;
    bool isPlaying = false;
    bool isDrawingLines = true;
    bool isLightMeshesVisible = true;
    bool isVsyncEnabled = true;
    bool isLightsEnabled = true;
    float previousFrame;
    float fps;
    float deltaTime;
    float currentFrame;
    std::vector<Mesh *> meshes;
    std::vector<Light *> pointLightMeshes;
    glm::vec4 backgroundColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

  private:
    std::string name;
    Camera *camera;
    GLFWwindow *window;
    Imgui *imgui;
    Line *xline;
    Line *yline;
    Line *zline;
    Line *originXLine;
    Line *originYLine;
    Line *originZLine;
  };
}

#endif