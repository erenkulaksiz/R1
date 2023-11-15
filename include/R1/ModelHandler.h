#ifndef MODEL_H
#define MODEL_h
#include <string>
#include <vector>
#include "Mesh.h"

namespace R1
{
  class ModelHandler
  {
  public:
    ModelHandler(std::string fileName);
    std::vector<Mesh *> loadMeshes(const char *vertexPath, const char *fragmentPath);

  private:
    std::vector<Mesh *> meshes;
    std::string fileName;
  };
};

#endif