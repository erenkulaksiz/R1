#include <glad/glad.h>
#include <iostream>
#include <string>
#include <R1/Texture.h>

R1::Texture::Texture(std::string imagePath, GLenum texType, GLenum slot, GLenum format, GLenum pixelType)
{
  std::cout << "Texture::Texture() " << imagePath << std::endl;
  this->texType = texType;
  this->imagePath = imagePath;
  this->slot = slot;
  this->format = format;
  this->pixelType = pixelType;
}

void R1::Texture::setup()
{
  std::cout << "Texture::setup()" << ID << std::endl;
  int widthImg, heightImg, numColCh;
  stbi_set_flip_vertically_on_load(true);
  unsigned char *bytes = stbi_load(imagePath.c_str(), &widthImg, &heightImg, &numColCh, 0);

  glGenTextures(1, &ID);
  glActiveTexture(slot);
  glBindTexture(texType, ID);

  glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
  glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

  // float flatColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
  // glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, flatColor);
  glTexImage2D(texType, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, bytes);
  glGenerateMipmap(texType);
  stbi_image_free(bytes);
  glBindTexture(texType, 0);
}

void R1::Texture::texUnit(Shader *shader, const char *uniform, GLuint unit)
{
  GLuint texUni = glGetUniformLocation(shader->ID, uniform);
  shader->activate();
  glUniform1i(texUni, unit);
}

void R1::Texture::bind()
{
  glBindTexture(texType, ID);
}

void R1::Texture::unbind()
{
  glBindTexture(texType, 0);
}

void R1::Texture::cleanup()
{
  std::cout << "Texture::cleanup()" << ID << std::endl;
  glDeleteTextures(1, &ID);
}