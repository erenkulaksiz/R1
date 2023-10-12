#ifndef LINE_H
#define LINE_H
#include <GLFW/glfw3.h>
#include <R1/Mesh.h>
#include <vector>

namespace R1
{
  class Line
  {
  public:
    Line(glm::vec3 end);
    void cleanup();
    void setPosition(glm::vec3 position);
    void setRotation(glm::vec3 rotation);
    void setColor(glm::vec4 color);
    void render(glm::mat4 viewMatrix, glm::mat4 projectionMatrix);

  private:
    Shader *lineShader;
    glm::vec3 position = glm::vec3(0, 0, 0);
    glm::vec3 rotation = glm::vec3(0, 0, 0);
    glm::vec4 color = glm::vec4(1, 1, 1, 1);
    VAO *vao;
    VBO *vbo;
    EBO *ebo;
  };
}

#endif
