#include <iostream>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <R1/Shader/Shader.h>
#include <R1/Light.h>

R1::Light::Light(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, float *vertices, unsigned int *indices, size_t vertexCount, size_t indexCount, Shader *shader) : Mesh(position, rotation, scale, vertices, indices, vertexCount, indexCount, shader)
{
  std::cout << "Light::Light()" << std::endl;
  this->vertices = vertices;
  this->indices = indices;
  this->vertexCount = vertexCount;
  this->indexCount = indexCount;
  this->position = position;
  this->rotation = rotation;
  this->scale = scale;
  this->shader = shader;

  isBillboard = true;
}

void R1::Light::setLightSourceColor(glm::vec4 color)
{
  lightSourceColor = color;

  if (lightSourceColorChangeCallback)
    lightSourceColorChangeCallback(lightSourceColor);
}

void R1::Light::setLightSourceColorChangeCallback(LightSourceColorChangeCallback callback)
{
  lightSourceColorChangeCallback = callback;
}

glm::vec4 R1::Light::getLightSourceColor()
{
  return lightSourceColor;
}

void R1::Light::setIsPointLight(bool isPointLight)
{
  this->isPointLight = isPointLight;
}

bool R1::Light::getIsPointLight()
{
  return isPointLight;
}

void R1::Light::setLightSourceIntensity(float intensity)
{
  lightSourceIntensity = intensity;
}

float R1::Light::getLightSourceIntensity()
{
  return lightSourceIntensity;
}

void R1::Light::setLightSourceAmbient(glm::vec3 ambient)
{
  lightSourceAmbient = ambient;
}

glm::vec3 R1::Light::getLightSourceAmbient()
{
  return lightSourceAmbient;
}

void R1::Light::setLightSourceDiffuse(glm::vec3 diffuse)
{
  lightSourceDiffuse = diffuse;
}

glm::vec3 R1::Light::getLightSourceDiffuse()
{
  return lightSourceDiffuse;
}

void R1::Light::setLightSourceSpecular(glm::vec3 specular)
{
  lightSourceSpecular = specular;
}

glm::vec3 R1::Light::getLightSourceSpecular()
{
  return lightSourceSpecular;
}

void R1::Light::setLightSourceConstant(float constant)
{
  lightSourceConstant = constant;
}

float R1::Light::getLightSourceConstant()
{
  return lightSourceConstant;
}

void R1::Light::setLightSourceLinear(float linear)
{
  lightSourceLinear = linear;
}

float R1::Light::getLightSourceLinear()
{
  return lightSourceLinear;
}

void R1::Light::setLightSourceQuadratic(float quadratic)
{
  lightSourceQuadratic = quadratic;
}

float R1::Light::getLightSourceQuadratic()
{
  return lightSourceQuadratic;
}

void R1::Light::render(Camera *camera)
{
  if (!isVisible)
  {
    return;
  }

  glDisable(GL_DEPTH_TEST);

  vao->bind();
  shader->activate();
  shader->setView(camera->getViewMatrix());
  shader->setProjection(camera->getProjectionMatrix());
  texture->bind();
  shader->setCameraPos(camera->getMesh()->getPosition());
  shader->setColor(lightSourceColor);
  shader->setBillboardPos(position);

  glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
}