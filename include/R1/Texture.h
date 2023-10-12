#ifndef TEXTURE_H
#define TEXTURE_H
#include <stb/stb_image.h>
#include <R1/shader/Shader.h>

typedef unsigned int GLuint;
typedef unsigned int GLenum;

namespace R1
{
  class Texture
  {
  public:
    Texture(const char *image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);
    void setup();
    void cleanup();
    GLuint ID;
    GLenum texType;
    const char *image;
    GLenum slot;
    GLenum format;
    GLenum pixelType;
    void texUnit(Shader *shader, const char *uniform, GLuint unit);
    void bind();
    void unbind();
  };
}

#endif