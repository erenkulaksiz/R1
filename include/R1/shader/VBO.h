#ifndef VBO_H
#define VBO_H

typedef unsigned int GLuint;
typedef float GLfloat;
typedef signed long long int GLsizeiptr;
typedef unsigned int GLenum;

namespace R1
{
  class VBO
  {
  public:
    VBO(GLfloat *vertices, GLsizeiptr size);
    void cleanup();
    GLuint ID;
    void bind();
    void unbind();
  };
}

#endif