#include <glad/glad.h>
#include <iostream>
#include <R1/Shader/VBO.h>

R1::VBO::VBO(GLfloat *vertices, GLsizeiptr size)
{
  glGenBuffers(1, &ID);
  glBindBuffer(GL_ARRAY_BUFFER, ID);
  glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
  std::cout << "VBO created with ID: " << ID << std::endl;
}

void R1::VBO::bind()
{
  glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void R1::VBO::unbind()
{
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void R1::VBO::cleanup()
{
  std::cout << "VBO::cleanup()" << ID << std::endl;
  glDeleteBuffers(1, &ID);
}