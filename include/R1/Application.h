#ifndef APPLICATION_H
#define APPLICATION_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <R1/Scene.h>

namespace R1
{
  class Application
  {
  public:
    Application();
    void cleanup();
    bool setup();
    Scene *scene;
    void loop();
    GLFWwindow *window;
    unsigned int screenWidth = 800;
    unsigned int screenHeight = 600;
    const char *title = "R1";
    static void ScreenSizeCallback(GLFWwindow *window, int width, int height)
    {
      Application *Application = static_cast<R1::Application *>(glfwGetWindowUserPointer(window));
      if (Application)
      {
        Application->screenWidth = width;
        Application->screenHeight = height;
        Application->scene->setScreenSize(width, height);
        glViewport(0, 0, width, height);
      }
    }
    static void ScrollCallback(GLFWwindow *window, double xoffset, double yoffset)
    {
      Application *app = static_cast<Application *>(glfwGetWindowUserPointer(window));
      if (app)
      {
        app->scene->getCamera()->handleScroll(yoffset);
      }
    }
    static void MousePositionCallback(GLFWwindow *window, double xpos, double ypos)
    {
      Application *app = static_cast<Application *>(glfwGetWindowUserPointer(window));
      if (app)
      {
        app->scene->getCamera()->handleMouse(xpos, ypos);
      }
    }
  };
}

#endif