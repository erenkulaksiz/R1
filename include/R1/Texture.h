#ifndef TEXTURE_H
#define TEXTURE_H
#include <stb/stb_image.h>
#include <string>
#include <R1/shader/Shader.h>

typedef unsigned int GLuint;
typedef unsigned int GLenum;

namespace R1
{
  class Texture
  {
  public:
    Texture(std::string imagePath, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);
    void texUnit(Shader *shader, const char *uniform, GLuint unit);
    void bind();
    void setup();
    void unbind();
    void cleanup();
    GLuint ID;
    GLenum slot;
    GLenum format;
    GLenum texType;
    GLenum pixelType;
    std::string imagePath;
  };
}

#endif