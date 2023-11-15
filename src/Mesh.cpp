#include <iostream>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <R1/shader/Shader.h>
#include <R1/shader/VAO.h>
#include <R1/shader/VBO.h>
#include <R1/shader/EBO.h>
#include <R1/Mesh.h>
#include <R1/Texture.h>

R1::Mesh::Mesh(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, float *vertices, unsigned int *indices, size_t vertexCount, size_t indexCount, Shader *shader)
{
  std::cout << "Mesh::Mesh(long one)" << std::endl;
  this->vertices = vertices;
  this->indices = indices;
  this->vertexCount = vertexCount;
  this->indexCount = indexCount;
  this->position = position;
  this->rotation = rotation;
  this->scale = scale;
  this->shader = shader;
}

R1::Mesh::Mesh(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, Shader *shader)
{
  std::cout << "Mesh::Mesh(middle)" << std::endl;
  this->position = position;
  this->rotation = rotation;
  this->scale = scale;
  this->shader = shader;
}

void R1::Mesh::setup()
{
  std::cout << "Mesh::setup()" << name << std::endl;

  vao = new VAO();
  vao->bind();

  vbo = new VBO(vertices, vertexCount);
  ebo = new EBO(indices, indexCount);

  vao->linkAttrib(*vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), (void *)0);
  vao->linkAttrib(*vbo, 1, 2, GL_FLOAT, 8 * sizeof(float), (void *)(3 * sizeof(float)));
  vao->linkAttrib(*vbo, 2, 3, GL_FLOAT, 8 * sizeof(float), (void *)(5 * sizeof(float)));
  vao->unbind();
  vbo->unbind();
  ebo->unbind();
}

R1::Mesh::Mesh()
{
  std::cout << "Mesh::Mesh() no args" << std::endl;
}

void R1::Mesh::setVertices(float *vertices, size_t vertexCount)
{
  this->vertices = vertices;
  this->vertexCount = vertexCount;
}

void R1::Mesh::setIndices(unsigned int *indices, size_t indexCount)
{
  this->indices = indices;
  this->indexCount = indexCount;
}

int R1::Mesh::getVerticesCount()
{
  return vertexCount;
}

void R1::Mesh::setCamera(Camera &camera)
{
  this->camera = &camera;
}

R1::Camera *R1::Mesh::getCamera()
{
  return camera;
}

void R1::Mesh::deleteCamera()
{
  if (!camera)
    return;
  camera = nullptr;
  isCameraDeleted = true;
}

bool R1::Mesh::getIsCameraDeleted()
{
  return isCameraDeleted;
}

void R1::Mesh::setOnPositionChangeCallback(PositionChangeCallback callback)
{
  positionChangeCallback = callback;
}

void R1::Mesh::setOnRotationChangeCallback(RotationChangeCallback callback)
{
  rotationChangeCallback = callback;
}

void R1::Mesh::setOnScaleChangeCallback(ScaleChangeCallback callback)
{
  scaleChangeCallback = callback;
}

void R1::Mesh::setName(std::string name)
{
  this->name = name;
}

std::string R1::Mesh::getName()
{
  return name;
}

void R1::Mesh::setPosition(glm::vec3 position)
{
  this->position = position;

  if (positionChangeCallback != nullptr)
  {
    positionChangeCallback(position);
  }
}

void R1::Mesh::setRotation(glm::vec3 rotation)
{
  this->rotation = rotation;

  if (rotationChangeCallback != nullptr)
  {
    rotationChangeCallback(rotation);
  }
}

void R1::Mesh::setScale(glm::vec3 scale)
{
  this->scale = scale;

  if (scaleChangeCallback != nullptr)
  {
    scaleChangeCallback(scale);
  }
}

glm::vec3 R1::Mesh::getPosition()
{
  return position;
}

glm::vec3 R1::Mesh::getRotation()
{
  return rotation;
}

glm::vec3 R1::Mesh::getScale()
{
  return scale;
}

int R1::Mesh::getVertexCount()
{
  return vertexCount;
}

int R1::Mesh::getIndexCount()
{
  return indexCount;
}

void R1::Mesh::setIsSelected(bool isSelected)
{
  this->isSelected = isSelected;
}

bool R1::Mesh::getIsSelected()
{
  return isSelected;
}

void R1::Mesh::setIsBillboard(bool isBillboard)
{
  this->isBillboard = isBillboard;
}

void R1::Mesh::setIsCamera(bool isCamera)
{
  this->isCamera = isCamera;
}

void R1::Mesh::setColor(glm::vec4 color)
{
  this->color = color;
}

glm::vec4 R1::Mesh::getColor()
{
  return color;
}

bool R1::Mesh::getIsTextured()
{
  return isTextured;
}

bool R1::Mesh::getIsBillboard()
{
  return isBillboard;
}

bool R1::Mesh::getIsCamera()
{
  return isCamera;
}

void R1::Mesh::setIsCameraDeleted(bool isCameraDeleted)
{
  this->isCameraDeleted = isCameraDeleted;
}

void R1::Mesh::setShader(Shader &shader)
{
  this->shader = &shader;
}

R1::Shader *R1::Mesh::getShader()
{
  return shader;
}

void R1::Mesh::setIsVisible(bool isVisible)
{
  this->isVisible = isVisible;
}

bool R1::Mesh::getIsVisible()
{
  return isVisible;
}

glm::vec3 R1::Mesh::getFront()
{
  return glm::vec3(0.0f, 0.0f, -1.0f);
}

glm::vec3 R1::Mesh::getUp()
{
  return glm::vec3(0.0f, 1.0f, 0.0f);
}

std::vector<R1::Texture *> R1::Mesh::getTextures()
{
  return textures;
}

void R1::Mesh::setIsSkybox(bool isSkybox)
{
  this->isSkybox = isSkybox;
}

bool R1::Mesh::getIsSkybox()
{
  return isSkybox;
}

void R1::Mesh::setIsDepthTestEnabled(bool isDepthTestEnabled)
{
  this->isDepthTestEnabled = isDepthTestEnabled;
}

bool R1::Mesh::getIsDepthTestEnabled()
{
  return isDepthTestEnabled;
}

void R1::Mesh::setIsWireframeEnabled(bool isWireframeEnabled)
{
  this->isWireframeEnabled = isWireframeEnabled;
}

bool R1::Mesh::getIsWireframeEnabled()
{
  return isWireframeEnabled;
}

void R1::Mesh::addTexture(Texture *texture)
{
  std::cout << "Mesh::addTexture() " << texture->imagePath << std::endl;
  textures.push_back(texture);
  if (textures.size() > 1 && isMultipleTextured == false)
  {
    std::cout << "Mesh::addTexture() textures.size() > 1"
              << " " << textures.size() << std::endl;
    isMultipleTextured = true;
  }
  isTextured = true;
}

void R1::Mesh::render(Camera *camera, std::vector<Light *> pointLightMeshes, std::vector<Light *> directionalLightMeshes, std::vector<Light *> spotLightMeshes, bool *isLightsEnabled, bool *isGlobalWireframeEnabled)
{
  if (isCamera || !isVisible)
  {
    return;
  }

  if (isSkybox)
  {
    glDepthFunc(GL_LEQUAL);
    position = camera->getMesh()->getPosition();
  }
  else
  {
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
  }

  if (isDepthTestEnabled)
  {
    glEnable(GL_DEPTH_TEST);
  }
  else
  {
    glDisable(GL_DEPTH_TEST);
  }

  if (isWireframeEnabled || *isGlobalWireframeEnabled)
  {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  }
  else
  {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }

  vao->bind();
  shader->activate();

  glm::mat4 model = glm::mat4(1.0f);
  model = glm::translate(model, position);
  model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
  model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
  model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
  model = glm::scale(model, scale);

  shader->setModel(model);
  shader->setView(camera->getViewMatrix());
  shader->setProjection(camera->getProjectionMatrix());

  if (*isLightsEnabled)
  {
    shader->setLightsEnabled(true);
  }
  else
  {
    shader->setLightsEnabled(false);
  }

  if (isTextured)
  {
    textures[0]->bind();
  }

  shader->setCameraPos(camera->getMesh()->getPosition());

  for (int i = 0; i < pointLightMeshes.size(); i++)
  {
    if (!pointLightMeshes[i]->getIsVisible())
    {
      shader->setLightBool(i, "pointLight", "enabled", false);
      continue;
    }
    shader->setLightBool(i, "pointLight", "enabled", true);
    shader->setLightVec4(i, "pointLight", "color", pointLightMeshes[i]->getLightSourceColor());
    shader->setLightVec3(i, "pointLight", "position", pointLightMeshes[i]->getPosition());
    shader->setLightFloat(i, "pointLight", "intensity", pointLightMeshes[i]->getLightSourceIntensity());
    shader->setLightVec3(i, "pointLight", "ambient", pointLightMeshes[i]->getLightSourceAmbient());
    shader->setLightVec3(i, "pointLight", "diffuse", pointLightMeshes[i]->getLightSourceDiffuse());
    shader->setLightVec3(i, "pointLight", "specular", pointLightMeshes[i]->getLightSourceSpecular());
    shader->setLightFloat(i, "pointLight", "constant", pointLightMeshes[i]->getLightSourceConstant());
    shader->setLightFloat(i, "pointLight", "linear", pointLightMeshes[i]->getLightSourceLinear());
    shader->setLightFloat(i, "pointLight", "quadratic", pointLightMeshes[i]->getLightSourceQuadratic());
  }

  for (int i = 0; i < directionalLightMeshes.size(); i++)
  {
    if (!directionalLightMeshes[i]->getIsVisible())
    {
      shader->setLightBool(i, "directionalLight", "enabled", false);
      continue;
    }
    shader->setLightBool(i, "directionalLight", "enabled", true);
    shader->setLightVec4(i, "directionalLight", "color", directionalLightMeshes[i]->getLightSourceColor());
    shader->setLightVec3(i, "directionalLight", "direction", directionalLightMeshes[i]->getLightSourceDirection());
    shader->setLightFloat(i, "directionalLight", "intensity", directionalLightMeshes[i]->getLightSourceIntensity());
    shader->setLightVec3(i, "directionalLight", "ambient", directionalLightMeshes[i]->getLightSourceAmbient());
    shader->setLightVec3(i, "directionalLight", "diffuse", directionalLightMeshes[i]->getLightSourceDiffuse());
    shader->setLightVec3(i, "directionalLight", "specular", directionalLightMeshes[i]->getLightSourceSpecular());
  }

  shader->setPointLightCount(pointLightMeshes.size());
  shader->setDirectionalLightCount(directionalLightMeshes.size());
  shader->setMaterialShininess(1.0f);

  if (isBillboard)
  {
    shader->setBillboardPos(position);
  }

  glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
}

R1::Mesh::~Mesh()
{
  std::cout << "Mesh::~Mesh()" << std::endl;
  cleanup();
}

void R1::Mesh::cleanup()
{
  std::cout << "Mesh::cleanup()" << name << std::endl;
  if (isCamera)
  {
    std::cout << "Mesh::cleanup() isCamera" << std::endl;
    return;
  }
  positionChangeCallback = nullptr;
  rotationChangeCallback = nullptr;
  scaleChangeCallback = nullptr;
  if (isTextured)
  {
    for (Texture *texture : textures)
    {
      texture->cleanup();
    }
  }
  vao->cleanup();
  vbo->cleanup();
  ebo->cleanup();
  shader->cleanup();
  isVisible = false;
  isTextured = false;
  isSelected = false;
}