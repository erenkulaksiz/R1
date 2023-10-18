#include <iostream>
#include <R1/Application.h>

R1::Application::Application()
{
  std::cout << "Application::Application()" << std::endl;
}

bool R1::Application::setup()
{
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
  glfwWindowHint(GLFW_SAMPLES, 4);

  window = glfwCreateWindow(screenWidth, screenHeight, title, NULL, NULL);

  if (window == NULL)
  {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return false;
  }

  int count;
  int windowWidth, windowHeight;
  int monitorX, monitorY;
  GLFWmonitor **monitors = glfwGetMonitors(&count);
  const GLFWvidmode *videoMode = glfwGetVideoMode(monitors[0]);
  windowWidth = videoMode->width / 1.5;
  windowHeight = windowWidth / 16 * 9;

  glfwMakeContextCurrent(window);
  glfwSetWindowPos(window,
                   monitorX + (videoMode->width - windowWidth) / 2,
                   monitorY + (videoMode->height - windowHeight) / 2);
  glfwShowWindow(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return false;
  }

  glfwSetWindowUserPointer(window, this);
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  glfwSetFramebufferSizeCallback(window, ScreenSizeCallback);
  glfwSetCursorPosCallback(window, MousePositionCallback);
  glfwSetScrollCallback(window, ScrollCallback);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_MULTISAMPLE);

  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  glFrontFace(GL_CCW);

  scene = new Scene(window);
  scene->setup();

  std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
  std::cout << "OpenGL Vendor: " << glGetString(GL_VENDOR) << std::endl;
  std::cout << "OpenGL Renderer: " << glGetString(GL_RENDERER) << std::endl;
  std::cout << "OpenGL Shading Language Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
  std::cout << "Application::setup() Finished Setup" << std::endl;

  return true;
}

void R1::Application::loop()
{
  scene->loop();
}

void R1::Application::cleanup()
{
  std::cout << "Application shutting down." << std::endl;
  std::cout << "Application::cleanup()" << std::endl;
  glfwTerminate();
  scene->cleanup();
}