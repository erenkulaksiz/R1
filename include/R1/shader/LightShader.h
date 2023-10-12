#ifndef LIGHTSHADER_H
#define LIGHTSHADER_H
#include <glm/glm.hpp>
#include <string>
#include <R1/shader/LightShader.h>

std::string getFileContents(const char *filename);

typedef unsigned int GLuint;

namespace R1
{
  class LightShader : public Shader
  {
  public:
    LightShader(const char *vertexPath, const char *fragmentPath);
    void setPointLightColor(int index, glm::vec4 color);
    void setPointLightPos(int index, glm::vec3 pos);
    void setPointLightAmbient(int index, glm::vec3 ambient);
    void setPointLightDiffuse(int index, glm::vec3 diffuse);
    void setPointLightSpecular(int index, glm::vec3 specular);
    void setPointLightConstant(int index, float constant);
    void setPointLightLinear(int index, float linear);
    void setPointLightQuadratic(int index, float quadratic);
    void setPointLightCount(int count);
    void setMaterialShininess(float shininess);
  };
};

#include <R1/shader/Shader.h>
#endif