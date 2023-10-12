#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <R1/Line.h>
#include <R1/Shader/Shader.h>

R1::Line::Line(glm::vec3 end)
{
  lineShader = new Shader("shaders/line.vert", "shaders/line.frag");
  lineShader->setup();

  vao = new VAO();
  vao->bind();

  float lineVertices[6] = {
      0.0f, 0.0f, 0.0f,
      end.x, end.y, end.z};

  unsigned int lineIndices[2] = {
      0, 1};

  vbo = new VBO(lineVertices, sizeof(lineVertices));
  ebo = new EBO(lineIndices, sizeof(lineIndices));

  vao->linkVBO(*vbo, 0);
  vao->unbind();
  vbo->unbind();
  ebo->unbind();
}

void R1::Line::setRotation(glm::vec3 rotation)
{
  this->rotation = rotation;
}

void R1::Line::setPosition(glm::vec3 position)
{
  this->position = position;
}

void R1::Line::setColor(glm::vec4 color)
{
  this->color = color;
}

void R1::Line::render(glm::mat4 viewMatrix, glm::mat4 projectionMatrix)
{
  vao->bind();
  lineShader->activate();

  glm::mat4 model = glm::mat4(1.0f);
  model = glm::translate(model, position);
  model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1, 0, 0));
  model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0, 1, 0));
  model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0, 0, 1));
  model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

  lineShader->setModel(model);
  lineShader->setView(viewMatrix);
  lineShader->setProjection(projectionMatrix);
  lineShader->setVec4("color", color);

  glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, 0);
}

void R1::Line::cleanup()
{
  std::cout << "Line::cleanup()" << std::endl;
}