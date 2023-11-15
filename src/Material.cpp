#include <R1/Material.h>
#include <iostream>

R1::Material::Material()
{
  std::cout << "Material::Material()" << std::endl;
}

void R1::Material::setAmbient(glm::vec3 ambient)
{
  std::cout << "Material::setAmbient()" << std::endl;
  this->ambient = ambient;
}

void R1::Material::setDiffuse(glm::vec3 diffuse)
{
  std::cout << "Material::setDiffuse()" << std::endl;
  this->diffuse = diffuse;
}

void R1::Material::setSpecular(glm::vec3 specular)
{
  std::cout << "Material::setSpecular()" << std::endl;
  this->specular = specular;
}

void R1::Material::setShininess(float shininess)
{
  std::cout << "Material::setShininess()" << std::endl;
  this->shininess = shininess;
}

glm::vec3 R1::Material::getAmbient()
{
  std::cout << "Material::getAmbient()" << std::endl;
  return ambient;
}

glm::vec3 R1::Material::getDiffuse()
{
  std::cout << "Material::getDiffuse()" << std::endl;
  return diffuse;
}

glm::vec3 R1::Material::getSpecular()
{
  std::cout << "Material::getSpecular()" << std::endl;
  return specular;
}

float R1::Material::getShininess()
{
  std::cout << "Material::getShininess()" << std::endl;
  return shininess;
}

void R1::Material::cleanup()
{
  std::cout << "Material::cleanup()" << std::endl;
  for (Texture *texture : textures)
  {
    texture->cleanup();
  }
}

void R1::Material::addTexture(Texture *texture)
{
  textures.push_back(texture);
}

std::vector<R1::Texture *> R1::Material::getTextures()
{
  return textures;
}