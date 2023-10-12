#include <iostream>
#include <glad/glad.h>
#include <R1/Shader/VAO.h>

R1::VAO::VAO()
{
  glGenVertexArrays(1, &ID);
  std::cout << "VAO created with ID: " << ID << std::endl;
}

void R1::VAO::linkAttrib(VBO &VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void *offset)
{
  VBO.bind();
  glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
  glEnableVertexAttribArray(layout);
  VBO.unbind();
}

void R1::VAO::linkVBO(VBO &VBO, GLuint layout)
{
  VBO.bind();
  glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
  glEnableVertexAttribArray(layout);
  VBO.unbind();
}

void R1::VAO::bind()
{
  // std::cout << "VAO::bind()" << &ID << std::endl;
  glBindVertexArray(ID);
}

void R1::VAO::unbind()
{
  glBindVertexArray(0);
}

void R1::VAO::cleanup()
{
  std::cout << "VAO::cleanup()" << ID << std::endl;
  glDeleteVertexArrays(1, &ID);
}