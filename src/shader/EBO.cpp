#include <glad/glad.h>
#include <iostream>
#include <R1/Shader/EBO.h>

R1::EBO::EBO(GLuint *indices, GLsizeiptr size)
{
  glGenBuffers(1, &ID);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
  std::cout << "EBO created with ID: " << ID << std::endl;
}

void R1::EBO::bind()
{
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void R1::EBO::unbind()
{
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void R1::EBO::cleanup()
{
  std::cout << "EBO::cleanup()" << ID << std::endl;
  glDeleteBuffers(1, &ID);
}