#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>
#include <filesystem>
#include <string>
#include <R1/ModelHandler.h>
#include <R1/Texture.h>

R1::ModelHandler::ModelHandler(std::string fileName)
{
  std::cout << "Model::Model()" << std::endl;
  this->fileName = fileName;
}

std::vector<R1::Mesh *> R1::ModelHandler::loadMeshes(const char *vertexPath, const char *fragmentPath)
{
  std::cout << "Model::loadMeshes()" << std::endl;

  Assimp::Importer importer;
  const aiScene *scene = importer.ReadFile(fileName, aiProcess_JoinIdenticalVertices | aiProcess_Triangulate);

  if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
  {
    std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
    return meshes;
  }

  for (unsigned int i = 0; i < scene->mNumMeshes; i++)
  {
    aiMesh *mesh = scene->mMeshes[i];
    Shader *shader = new Shader(vertexPath, fragmentPath);
    shader->setup();
    Mesh *model = new Mesh(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f), glm::vec3(1.0f), shader);
    model->setName(mesh->mName.C_Str());
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture *> textures;
    vertices.reserve(mesh->mNumVertices * 8);
    indices.reserve(mesh->mNumFaces * 3);

    if (scene->mNumMaterials == 0)
    {
      std::cout << "no materials for object - file " << fileName << std::endl;
    }

    for (int j = 0; j < scene->mNumMaterials; j++)
    {
      aiMaterial *material = scene->mMaterials[j];
      aiString texturePath;
      if (material->GetTexture(aiTextureType_DIFFUSE, 0, &texturePath) == AI_SUCCESS)
      {
        std::string textureFilePath = "resources/" + std::string(texturePath.C_Str());

        if (texturePath.length > 0)
        {
          std::cout << "diffuse texture path: " << textureFilePath << std::endl;

          /*
          aiUVTransform uvTransform;
          if (material->Get(AI_MATKEY_UVTRANSFORM(aiTextureType_DIFFUSE, 0), uvTransform) == AI_SUCCESS)
          {
            std::cout << "uv transform: " << uvTransform.mTranslation.x << ", " << uvTransform.mTranslation.y << std::endl;
            std::cout << "uv transform: " << uvTransform.mScaling.x << ", " << uvTransform.mScaling.y << std::endl;
            std::cout << "uv transform: " << uvTransform.mRotation << std::endl;
          }
          */

          Texture *diffuseTexture = new Texture(textureFilePath, GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE);
          diffuseTexture->setup();
          diffuseTexture->texUnit(shader, "material.diffuse", 0);
          diffuseTexture->isDiffuse = true;
          model->addTexture(diffuseTexture);
        }
      }

      if (material->GetTexture(aiTextureType_HEIGHT, 0, &texturePath) == AI_SUCCESS)
      {
        std::string textureFilePath = "resources/" + std::string(texturePath.C_Str());

        if (texturePath.length > 0)
        {
          std::cout << "normal texture path: " << textureFilePath << std::endl;

          /*
          aiUVTransform uvTransform;
          if (material->Get(AI_MATKEY_UVTRANSFORM(aiTextureType_HEIGHT, 0), uvTransform) == AI_SUCCESS)
          {
            std::cout << "uv transform: " << uvTransform.mTranslation.x << ", " << uvTransform.mTranslation.y << std::endl;
            std::cout << "uv transform: " << uvTransform.mScaling.x << ", " << uvTransform.mScaling.y << std::endl;
            std::cout << "uv transform: " << uvTransform.mRotation << std::endl;
          }
          */

          Texture *normalTexture = new Texture(textureFilePath, GL_TEXTURE_2D, GL_TEXTURE1, GL_UNSIGNED_BYTE);
          normalTexture->setup();
          normalTexture->texUnit(shader, "material.normalMap", 1);
          normalTexture->isNormal = true;
          model->addTexture(normalTexture);
        }
      }
    }

    for (unsigned int j = 0; j < mesh->mNumVertices; j++)
    {
      vertices.push_back(mesh->mVertices[j].x);
      vertices.push_back(mesh->mVertices[j].y);
      vertices.push_back(mesh->mVertices[j].z);

      if (mesh->HasTextureCoords(0))
      {
        vertices.push_back(mesh->mTextureCoords[0][j].x);
        vertices.push_back(mesh->mTextureCoords[0][j].y);
      }
      else
      {
        vertices.push_back(0.0f);
        vertices.push_back(0.0f);
      }

      vertices.push_back(mesh->mNormals[j].x);
      vertices.push_back(mesh->mNormals[j].y);
      vertices.push_back(mesh->mNormals[j].z);
    }

    model->setVertices(vertices.data(), sizeof(vertices[0]) * vertices.size());

    for (unsigned int j = 0; j < mesh->mNumFaces; j++)
    {
      if (mesh->mFaces[j].mNumIndices < 3)
      {
        continue;
      }
      for (unsigned int k = 0; k < mesh->mFaces[j].mNumIndices; k++)
      {
        indices.push_back(mesh->mFaces[j].mIndices[k]);
      }
    }

    model->setIndices(indices.data(), sizeof(indices[0]) * indices.size());
    model->setup();
    meshes.push_back(model);
  }

  return meshes;
}