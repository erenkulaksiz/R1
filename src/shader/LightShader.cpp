#include <iostream>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <R1/shader/Shader.h>
#include <R1/shader/LightShader.h>

R1::LightShader::LightShader(const char *vertexPath, const char *fragmentPath) : Shader(vertexPath, fragmentPath)
{
  std::cout << "LightShader::LightShader()" << std::endl;
  std::cout << "vertexPath: " << vertexPath << std::endl;
  std::cout << "fragmentPath: " << fragmentPath << std::endl;
  this->vertexPath = vertexPath;
  this->fragmentPath = fragmentPath;
}

void R1::LightShader::setPointLightColor(int index, glm::vec4 color)
{
  std::string uniformName = "pointLights[" + std::to_string(index) + "].color";
  const GLchar *uniformNameCStr = uniformName.c_str();
  glUniform4fv(glGetUniformLocation(ID, uniformNameCStr), 1, glm::value_ptr(color));
}

void R1::LightShader::setPointLightPos(int index, glm::vec3 pos)
{
  std::string uniformName = "pointLights[" + std::to_string(index) + "].position";
  const GLchar *uniformNameCStr = uniformName.c_str();
  glUniform3fv(glGetUniformLocation(ID, uniformNameCStr), 1, glm::value_ptr(pos));
}

void R1::LightShader::setPointLightAmbient(int index, glm::vec3 ambient)
{
  std::string uniformName = "pointLights[" + std::to_string(index) + "].ambient";
  const GLchar *uniformNameCStr = uniformName.c_str();
  glUniform3fv(glGetUniformLocation(ID, uniformNameCStr), 1, glm::value_ptr(ambient));
}

void R1::LightShader::setPointLightDiffuse(int index, glm::vec3 diffuse)
{
  std::string uniformName = "pointLights[" + std::to_string(index) + "].diffuse";
  const GLchar *uniformNameCStr = uniformName.c_str();
  glUniform3fv(glGetUniformLocation(ID, uniformNameCStr), 1, glm::value_ptr(diffuse));
}

void R1::LightShader::setPointLightSpecular(int index, glm::vec3 specular)
{
  std::string uniformName = "pointLights[" + std::to_string(index) + "].specular";
  const GLchar *uniformNameCStr = uniformName.c_str();
  glUniform3fv(glGetUniformLocation(ID, uniformNameCStr), 1, glm::value_ptr(specular));
}

void R1::LightShader::setPointLightConstant(int index, float constant)
{
  std::string uniformName = "pointLights[" + std::to_string(index) + "].constant";
  const GLchar *uniformNameCStr = uniformName.c_str();
  glUniform1f(glGetUniformLocation(ID, uniformNameCStr), constant);
}

void R1::LightShader::setPointLightLinear(int index, float linear)
{
  std::string uniformName = "pointLights[" + std::to_string(index) + "].linear";
  const GLchar *uniformNameCStr = uniformName.c_str();
  glUniform1f(glGetUniformLocation(ID, uniformNameCStr), linear);
}

void R1::LightShader::setPointLightQuadratic(int index, float quadratic)
{
  std::string uniformName = "pointLights[" + std::to_string(index) + "].quadratic";
  const GLchar *uniformNameCStr = uniformName.c_str();
  glUniform1f(glGetUniformLocation(ID, uniformNameCStr), quadratic);
}

void R1::LightShader::setPointLightCount(int count)
{
  glUniform1i(glGetUniformLocation(ID, "numberOfPointLights"), count);
}

void R1::LightShader::setMaterialShininess(float shininess)
{
  glUniform1f(glGetUniformLocation(ID, "material.shininess"), shininess);
}