#ifndef MATERIAL_H
#define MATERIAL_H
#include <glm/glm.hpp>
#include <vector>
#include <R1/Texture.h>

namespace R1
{
  class Material
  {
  public:
    Material();
    void cleanup();
    void addTexture(Texture *texture);
    void setAmbient(glm::vec3 ambient);
    void setDiffuse(glm::vec3 diffuse);
    void setSpecular(glm::vec3 specular);
    void setShininess(float shininess);
    glm::vec3 getAmbient();
    glm::vec3 getDiffuse();
    glm::vec3 getSpecular();
    float getShininess();
    std::vector<Texture *> getTextures();

  private:
    std::vector<Texture *> textures;
    glm::vec3 ambient = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 diffuse = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 specular = glm::vec3(0.0f, 0.0f, 0.0f);
    float shininess = 0.0f;
  };
};

#endif