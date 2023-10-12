#ifndef EBO_H
#define EBO_H

typedef unsigned int GLuint;
typedef signed long long int GLsizeiptr;

namespace R1
{
  class EBO
  {
  public:
    EBO(GLuint *indices, GLsizeiptr size);
    void cleanup();
    GLuint ID;
    void bind();
    void unbind();
  };
}

#endif