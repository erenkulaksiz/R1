#ifndef MESH_H
#define MESH_H
#include <vector>
#include <functional>
#include <R1/Shader/Shader.h>
#include <R1/Shader/VAO.h>
#include <R1/Shader/VBO.h>
#include <R1/Shader/EBO.h>
#include <R1/Camera.h>
#include <R1/Texture.h>

namespace R1
{
  class Camera;
  class Light;
}

typedef std::function<void(glm::vec3)> PositionChangeCallback;
typedef std::function<void(glm::vec3)> RotationChangeCallback;
typedef std::function<void(glm::vec3)> ScaleChangeCallback;

namespace R1
{
  class Mesh
  {
  public:
    Mesh(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, float *vertices, unsigned int *indices, size_t vertexCount, size_t indexCount, Shader *shader);
    Mesh();
    ~Mesh();
    void setup();
    void cleanup();
    void render(Camera *camera, std::vector<Light *> pointLightMeshes);
    void setPosition(glm::vec3 position);
    void setRotation(glm::vec3 rotation);
    void setScale(glm::vec3 scale);
    void setName(std::string name);
    void setCamera(Camera &camera);
    void setColor(glm::vec4 color);
    void setTexture(Texture *texture);
    void setShader(Shader &shader);
    void setIsSelected(bool isSelected);
    void setIsBillboard(bool isBillboard);
    void setIsCamera(bool isCamera);
    void setIsCameraDeleted(bool isCameraDeleted);
    void setIsVisible(bool isVisible);
    void deleteCamera();
    Camera *getCamera();
    std::string getName();
    Shader *getShader();
    glm::vec3 getPosition();
    glm::vec3 getRotation();
    glm::vec3 getScale();
    glm::vec3 getFront();
    glm::vec3 getUp();
    glm::vec4 getColor();
    bool getIsSelected();
    bool getIsBillboard();
    bool getIsCamera();
    bool getIsCameraDeleted();
    bool getIsTextured();
    bool getIsVisible();
    int getVertexCount();
    int getIndexCount();
    PositionChangeCallback positionChangeCallback = nullptr;
    RotationChangeCallback rotationChangeCallback = nullptr;
    ScaleChangeCallback scaleChangeCallback = nullptr;
    void setOnPositionChangeCallback(PositionChangeCallback callback);
    void setOnRotationChangeCallback(RotationChangeCallback callback);
    void setOnScaleChangeCallback(ScaleChangeCallback callback);
    virtual bool getIsLightSource() const
    {
      return false;
    }

  protected:
    Texture *texture;
    Camera *camera;
    Shader *shader;
    std::string name;
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
    glm::vec4 color;
    bool isCameraDeleted = false;
    bool isBillboard = false;
    bool isSelected = false;
    bool isTextured = false;
    bool isCamera = false;
    bool isVisible = true;
    VAO *vao;
    VBO *vbo;
    EBO *ebo;
    float *vertices;
    unsigned int *indices;
    size_t vertexCount;
    size_t indexCount;
  };
};

#include <R1/Light.h>
#endif