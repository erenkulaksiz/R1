#ifndef VAO_H
#define VAO_H
#include "VBO.h"

namespace R1
{
  class VAO
  {
  public:
    GLuint ID;
    void cleanup();
    VAO();
    void linkAttrib(VBO &VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void *offset);
    void linkVBO(VBO &VBO, GLuint layout);
    void bind();
    void unbind();
  };
}

#endif