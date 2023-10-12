#include <R1/Application.h>

int main()
{
  R1::Application app;

  if (app.setup())
  {
    while (!glfwWindowShouldClose(glfwGetCurrentContext()))
    {
      app.loop();
    }
  }

  app.cleanup();
  return 0;
}