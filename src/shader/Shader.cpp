#include <iostream>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <R1/shader/Shader.h>

std::string getFileContents(const char *filename)
{
  std::FILE *fp = std::fopen(filename, "rb");
  std::cout << "Shader getFileContents() filename: " << filename << std::endl;
  if (fp)
  {
    std::cout << "Shader getFileContents() Reading file: " << filename << std::endl;
    std::string contents;
    std::fseek(fp, 0, SEEK_END);
    contents.resize(std::ftell(fp));
    std::rewind(fp);
    std::fread(&contents[0], 1, contents.size(), fp);
    std::fclose(fp);
    return (contents);
  }
  std::cout << "Error reading file: " << filename << std::endl;
  throw(errno);
}

R1::Shader::Shader(const char *vertexPath, const char *fragmentPath)
{
  std::cout << "Shader::Shader()" << std::endl;
  std::cout << "vertexPath: " << vertexPath << std::endl;
  std::cout << "fragmentPath: " << fragmentPath << std::endl;
  this->vertexPath = vertexPath;
  this->fragmentPath = fragmentPath;
}

void R1::Shader::setup()
{
  std::cout << "Shader::setup()" << vertexPath << std::endl;
  std::string vertexCode = getFileContents(vertexPath);
  std::string fragmentCode = getFileContents(fragmentPath);

  const char *vertexSource = vertexCode.c_str();
  const char *fragmentSource = fragmentCode.c_str();

  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexSource, NULL);
  glCompileShader(vertexShader);

  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
  glCompileShader(fragmentShader);

  ID = glCreateProgram();
  glAttachShader(ID, vertexShader);
  glAttachShader(ID, fragmentShader);
  glLinkProgram(ID);
  compileErrors(ID, "PROGRAM");

  std::cout << "Shader::setup()" << ID << std::endl;

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

void R1::Shader::setModel(glm::mat4 model)
{
  glUniformMatrix4fv(glGetUniformLocation(ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
}

void R1::Shader::setView(glm::mat4 view)
{
  glUniformMatrix4fv(glGetUniformLocation(ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
}

void R1::Shader::setProjection(glm::mat4 projection)
{
  glUniformMatrix4fv(glGetUniformLocation(ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
}

void R1::Shader::setVec4(const char *name, glm::vec4 value)
{
  glUniform4fv(glGetUniformLocation(ID, name), 1, glm::value_ptr(value));
}

void R1::Shader::setColor(glm::vec4 color)
{
  glUniform4fv(glGetUniformLocation(ID, "color"), 1, glm::value_ptr(color));
}

void R1::Shader::setCameraPos(glm::vec3 pos)
{
  glUniform3fv(glGetUniformLocation(ID, "camPos"), 1, glm::value_ptr(pos));
}

void R1::Shader::setPointLightColor(int index, glm::vec4 color)
{
  std::string uniformName = "pointLights[" + std::to_string(index) + "].color";
  const GLchar *uniformNameCStr = uniformName.c_str();
  glUniform4fv(glGetUniformLocation(ID, uniformNameCStr), 1, glm::value_ptr(color));
}

void R1::Shader::setPointLightPos(int index, glm::vec3 pos)
{
  std::string uniformName = "pointLights[" + std::to_string(index) + "].position";
  const GLchar *uniformNameCStr = uniformName.c_str();
  glUniform3fv(glGetUniformLocation(ID, uniformNameCStr), 1, glm::value_ptr(pos));
}

void R1::Shader::setPointLightAmbient(int index, glm::vec3 ambient)
{
  std::string uniformName = "pointLights[" + std::to_string(index) + "].ambient";
  const GLchar *uniformNameCStr = uniformName.c_str();
  glUniform3fv(glGetUniformLocation(ID, uniformNameCStr), 1, glm::value_ptr(ambient));
}

void R1::Shader::setPointLightDiffuse(int index, glm::vec3 diffuse)
{
  std::string uniformName = "pointLights[" + std::to_string(index) + "].diffuse";
  const GLchar *uniformNameCStr = uniformName.c_str();
  glUniform3fv(glGetUniformLocation(ID, uniformNameCStr), 1, glm::value_ptr(diffuse));
}

void R1::Shader::setPointLightSpecular(int index, glm::vec3 specular)
{
  std::string uniformName = "pointLights[" + std::to_string(index) + "].specular";
  const GLchar *uniformNameCStr = uniformName.c_str();
  glUniform3fv(glGetUniformLocation(ID, uniformNameCStr), 1, glm::value_ptr(specular));
}

void R1::Shader::setPointLightConstant(int index, float constant)
{
  std::string uniformName = "pointLights[" + std::to_string(index) + "].constant";
  const GLchar *uniformNameCStr = uniformName.c_str();
  glUniform1f(glGetUniformLocation(ID, uniformNameCStr), constant);
}

void R1::Shader::setPointLightLinear(int index, float linear)
{
  std::string uniformName = "pointLights[" + std::to_string(index) + "].linear";
  const GLchar *uniformNameCStr = uniformName.c_str();
  glUniform1f(glGetUniformLocation(ID, uniformNameCStr), linear);
}

void R1::Shader::setPointLightQuadratic(int index, float quadratic)
{
  std::string uniformName = "pointLights[" + std::to_string(index) + "].quadratic";
  const GLchar *uniformNameCStr = uniformName.c_str();
  glUniform1f(glGetUniformLocation(ID, uniformNameCStr), quadratic);
}

void R1::Shader::setPointLightIntensity(int index, float intensity)
{
  std::string uniformName = "pointLights[" + std::to_string(index) + "].intensity";
  const GLchar *uniformNameCStr = uniformName.c_str();
  glUniform1f(glGetUniformLocation(ID, uniformNameCStr), intensity);
}

void R1::Shader::setPointLightEnabled(int index, bool enabled)
{
  std::string uniformName = "pointLights[" + std::to_string(index) + "].enabled";
  const GLchar *uniformNameCStr = uniformName.c_str();
  glUniform1i(glGetUniformLocation(ID, uniformNameCStr), enabled);
}

void R1::Shader::setPointLightCount(int count)
{
  glUniform1i(glGetUniformLocation(ID, "numberOfPointLights"), count);
}

void R1::Shader::setMaterialShininess(float shininess)
{
  glUniform1f(glGetUniformLocation(ID, "material.shininess"), shininess);
}

void R1::Shader::setBillboardPos(glm::vec3 pos)
{
  glUniform3fv(glGetUniformLocation(ID, "billboardPos"), 1, glm::value_ptr(pos));
}

void R1::Shader::activate()
{
  glUseProgram(ID);
}

void R1::Shader::deactivate()
{
  glUseProgram(0);
}

GLuint R1::Shader::getId()
{
  return ID;
}

void R1::Shader::compileErrors(unsigned int shader, const char *type)
{
  GLint hasCompiled;
  char infoLog[1024];
  if (type != "PROGRAM")
  {
    glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
    if (hasCompiled == GL_FALSE)
    {
      glGetShaderInfoLog(shader, 1024, NULL, infoLog);
      std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n"
                << infoLog << std::endl;
    }
  }
  else
  {
    glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
    if (hasCompiled == GL_FALSE)
    {
      glGetProgramInfoLog(shader, 1024, NULL, infoLog);
      std::cout << "SHADER_LINKING_ERROR for:" << type << "\n"
                << infoLog << std::endl;
    }
  }
}

void R1::Shader::cleanup()
{
  std::cout << "Shader::cleanup()" << ID << std::endl;
  glDeleteProgram(ID);
}