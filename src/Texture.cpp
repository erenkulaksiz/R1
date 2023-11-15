#include <glad/glad.h>
#include <iostream>
#include <string>
#include <R1/Texture.h>

R1::Texture::Texture(std::string imagePath, GLenum texType, GLenum slot, GLenum pixelType)
{
  std::cout << "Texture::Texture() " << imagePath << std::endl;
  this->texType = texType;
  this->imagePath = imagePath;
  this->slot = slot;
  this->pixelType = pixelType;
}

R1::Texture::Texture(GLenum texType, GLenum slot, GLenum pixelType)
{
  std::cout << "Texture::Texture() " << imagePath << std::endl;
  this->texType = texType;
  this->imagePath = imagePath;
  this->slot = slot;
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

  glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
  glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

  GLenum format = GL_RED;
  if (numColCh == 1)
    format = GL_RED;
  else if (numColCh == 3)
    format = GL_RGB;
  else if (numColCh == 4)
    format = GL_RGBA;

  // float flatColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
  // glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, flatColor);
  glTexImage2D(texType, 0, format, widthImg, heightImg, 0, format, pixelType, bytes);
  glGenerateMipmap(texType);
  stbi_image_free(bytes);
  glBindTexture(texType, 0);
}

void R1::Texture::setupShadow()
{
  std::cout << "Texture::setupShadow()" << ID << std::endl;
  glGenFramebuffers(1, &ID);

  GLuint pointLightShadowMapTexture;
  glGenTextures(1, &pointLightShadowMapTexture);
  glBindTexture(GL_TEXTURE_2D, pointLightShadowMapTexture);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 1024, 1024, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
  GLfloat borderColor[] = {1.0, 1.0, 1.0, 1.0};
  glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

  glBindFramebuffer(GL_FRAMEBUFFER, ID);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, pointLightShadowMapTexture, 0);
  glDrawBuffer(GL_NONE);
  glReadBuffer(GL_NONE);
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
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

void R1::Texture::bindShadow()
{
  glBindFramebuffer(GL_FRAMEBUFFER, ID);
  glViewport(0, 0, 1024, 1024);
  glClear(GL_DEPTH_BUFFER_BIT);
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