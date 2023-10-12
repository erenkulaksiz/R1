#ifndef LIGHT_H
#define LIGHT_H
#include <functional>
#include <R1/Shader/Shader.h>
#include <R1/Mesh.h>

typedef std::function<void(glm::vec3)> LightSourceColorChangeCallback;

namespace R1
{
  class Light : public Mesh
  {
  public:
    Light(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, float *vertices, unsigned int *indices, size_t vertexCount, size_t indexCount, Shader *shader);
    void render(Camera *camera);
    void cleanup();
    void setLightSourceColor(glm::vec4 color);
    void setLightSourceColorChangeCallback(LightSourceColorChangeCallback callback);
    void setLightSourceIntensity(float intensity);
    void setLightSourceAmbient(glm::vec3 ambient);
    void setLightSourceDiffuse(glm::vec3 diffuse);
    void setLightSourceSpecular(glm::vec3 specular);
    void setLightSourceConstant(float constant);
    void setLightSourceLinear(float linear);
    void setLightSourceQuadratic(float quadratic);
    void setIsPointLight(bool isPointLight);
    bool getIsPointLight();
    float getLightSourceIntensity();
    glm::vec3 getLightSourceAmbient();
    glm::vec3 getLightSourceDiffuse();
    glm::vec3 getLightSourceSpecular();
    float getLightSourceConstant();
    float getLightSourceLinear();
    float getLightSourceQuadratic();
    glm::vec4 getLightSourceColor();
    LightSourceColorChangeCallback lightSourceColorChangeCallback = nullptr;
    bool getIsLightSource() const override
    {
      return true;
    }

  private:
    glm::vec3 lightSourceAmbient = glm::vec3(0.05f, 0.05f, 0.05f);
    glm::vec3 lightSourceDiffuse = glm::vec3(0.8f, 0.8f, 0.8f);
    glm::vec3 lightSourceSpecular = glm::vec3(1.0f, 1.0f, 1.0f);
    float lightSourceConstant = 1.0f;
    float lightSourceLinear = 0.09f;
    float lightSourceQuadratic = 0.032f;
    glm::vec4 lightSourceColor;
    float lightSourceIntensity = 1.0f;
    bool isPointLight = false;
  };
};

#endif