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
    Shader(const char *vertexPath, const char *fragmentPath, const char *geometryPath);
    void setup();
    void cleanup();
    GLuint ID;
    GLuint getId();
    void activate();
    void deactivate();
    void setModel(glm::mat4 model);
    void setView(glm::mat4 view);
    void setProjection(glm::mat4 projection);
    void setMat4(const char *name, glm::mat4 value);
    void setVec4(const char *name, glm::vec4 value);
    void setColor(glm::vec4 color);
    void setCameraPos(glm::vec3 pos);
    void setBillboardPos(glm::vec3 pos);
    void setLightsEnabled(bool enabled);

    void setLightFloat(int index, std::string lightType, std::string name, float value);
    void setLightVec3(int index, std::string lightType, std::string name, glm::vec3 value);
    void setLightVec4(int index, std::string lightType, std::string name, glm::vec4 value);
    void setLightBool(int index, std::string lightType, std::string name, bool value);

    void setPointLightCount(int count);
    void setDirectionalLightCount(int count);

    void setMaterialShininess(float shininess);

  protected:
    void compileErrors(unsigned int shader, const char *type);
    const char *vertexPath;
    const char *fragmentPath;
    const char *geometryPath;
  };
};

#endif