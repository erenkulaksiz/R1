#ifndef IMGUI_H
#define IMGUI_H
#include <GLFW/glfw3.h>
#include <R1/Mesh.h>
#include <vector>

namespace R1
{
  class Scene;

  class Imgui
  {
  public:
    Imgui();
    void setup();
    void setScene(Scene *scene);
    Scene *getScene();
    void cleanup();
    void newFrame();
    void render();
    void drawGui();
    void setMouseInteractions(bool value);
    bool mouseInteractions;

  private:
    Scene *scene;
    unsigned int selectedMeshIndex = -1;
    float positionVec3[3] = {0.0f, 0.0f, 0.0f};
    float rotationVec3[3] = {0.0f, 0.0f, 0.0f};
    float scaleVec3[3] = {1.0f, 1.0f, 1.0f};
  };
}

#endif
