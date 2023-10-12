#ifndef SHADER_H
#define SHADER_H
#include <glm/glm.hpp>
#include <string>

std::string getFileContents(const char *filename);

typedef unsigned int GLuint;

namespace R1
{
  class Shader
  {
  public:
    Shader(const char *vertexPath, const char *fragmentPath);
    void setup();
    void cleanup();
    GLuint ID;
    GLuint getId();
    void activate();
    void deactivate();
    void setModel(glm::mat4 model);
    void setView(glm::mat4 view);
    void setProjection(glm::mat4 projection);
    void setVec4(const char *name, glm::vec4 value);
    void setColor(glm::vec4 color);
    void setCameraPos(glm::vec3 pos);
    void setBillboardPos(glm::vec3 pos);
    void setPointLightColor(int index, glm::vec4 color);
    void setPointLightPos(int index, glm::vec3 pos);
    void setPointLightAmbient(int index, glm::vec3 ambient);
    void setPointLightDiffuse(int index, glm::vec3 diffuse);
    void setPointLightSpecular(int index, glm::vec3 specular);
    void setPointLightConstant(int index, float constant);
    void setPointLightLinear(int index, float linear);
    void setPointLightQuadratic(int index, float quadratic);
    void setPointLightIntensity(int index, float intensity);
    void setPointLightEnabled(int index, bool enabled);
    void setPointLightCount(int count);
    void setMaterialShininess(float shininess);

  protected:
    void compileErrors(unsigned int shader, const char *type);
    const char *vertexPath;
    const char *fragmentPath;
  };
};

#endif