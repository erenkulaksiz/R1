#include <iostream>
#include <glad/glad.h>
#include <R1/Scene.h>
#include <R1/Camera.h>
#include <R1/Line.h>
#include <R1/Light.h>

GLfloat cubeVertices[] = {
    //     COORDINATES     /        COLORS      /   TexCoord  /   normals
    // front face
    -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, // Front bottom-left
    0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f,  // Front bottom-right
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f,   // Front top-right
    -0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,  // Front top-left

    // Back face
    -0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, // Back bottom-left
    0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,  // Back bottom-right
    0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,   // Back top-right
    -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,  // Back top-left

    // Left face
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, // Left bottom-left
    -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,  // Left top-left
    -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f,   // Left top-right
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,  // Left bottom-right

    // Right face
    0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // Right bottom-left
    0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,  // Right top-left
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,   // Right top-right
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,  // Right bottom-right

    // Top face
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, // Top bottom-left
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,  // Top bottom-right
    0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,   // Top top-right
    -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,  // Top top-left

    // Bottom face
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, // Bottom bottom-left
    0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,  // Bottom bottom-right
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f,   // Bottom top-right
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f,  // Bottom top-left
};

GLuint cubeIndices[] = {
    // Front face
    0, 1, 2,
    2, 3, 0,

    // Back face
    4, 5, 6,
    6, 7, 4,

    // Left face
    8, 9, 10,
    10, 11, 8,

    // Right face
    12, 13, 14,
    14, 15, 12,

    // Top face
    16, 17, 18,
    18, 19, 16,

    // Bottom face
    20, 21, 22,
    22, 23, 20};

GLfloat planeVertices[] =
    {
        //     COORDINATES     /        COLORS      /   TexCoord  /   normals
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, // Lower left corner
        -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,  // Upper left corner
        0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,   // Upper right corner
        0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,  // Lower right corner
};

GLuint planeIndices[] =
    {
        0, 2, 1,
        0, 3, 2};

std::vector<glm::vec3> cubePositions = {
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3(2.0f, 4.0f, 2.0f),
    glm::vec3(2.0f, 0.0f, 0.0f),
};

R1::Scene::Scene(GLFWwindow *window)
{
  std::cout << "Scene::Scene()" << std::endl;
  this->window = window;
}

void R1::Scene::setup()
{
  std::cout << "Scene::setup()" << std::endl;
  imgui = new Imgui();
  imgui->setup();
  imgui->setScene(this);
  camera = new Camera(window);
  camera->setIsActiveCamera(true);
  camera->setScreenSize(screenWidth, screenHeight);
  camera->getMesh()->setPosition(glm::vec3(0.0f, 0.0f, 3.0f));
  camera->getMesh()->setName("debugCamera");
  camera->getMesh()->setCamera(*camera);
  meshes.push_back(camera->getMesh());

  Camera *camera2 = new Camera(window);
  camera2->setScreenSize(screenWidth, screenHeight);
  camera2->getMesh()->setPosition(glm::vec3(0.0f, 5.0f, 3.0f));
  camera2->getMesh()->setName("camera_test_2");
  camera2->getMesh()->setIsCamera(true);
  camera2->getMesh()->setCamera(*camera2);
  meshes.push_back(camera2->getMesh());

  originXLine = new Line(glm::vec3(5.0f, 0.0f, 0.0f));
  originYLine = new Line(glm::vec3(0.0f, 5.0f, 0.0f));
  originZLine = new Line(glm::vec3(0.0f, 0.0f, 5.0f));
  originXLine->setColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
  originYLine->setColor(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
  originZLine->setColor(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
  xline = new Line(glm::vec3(1.0f, 0.0f, 0.0f));
  yline = new Line(glm::vec3(0.0f, 1.0f, 0.0f));
  zline = new Line(glm::vec3(0.0f, 0.0f, 1.0f));
  xline->setColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
  yline->setColor(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
  zline->setColor(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));

  Shader *texturedShader = new Shader("shaders/default_light.vert", "shaders/default_light.frag");
  texturedShader->setup();
  Texture *defaultTexture = new Texture("resources/default3.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
  defaultTexture->setup();
  defaultTexture->texUnit(texturedShader, "tex0", 0);

  for (int index = 0; index < cubePositions.size(); ++index)
  {
    const glm::vec3 &position = cubePositions[index];
    glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    if (index == 1)
    {
      rotation = glm::vec3(0.0f, 45.0f, 0.0f);
    }
    Mesh *mesh = new Mesh(position, rotation, glm::vec3(1.0f), cubeVertices, cubeIndices, sizeof(cubeVertices), sizeof(cubeIndices), texturedShader);
    mesh->setup();
    mesh->setName("cube " + std::to_string(index));
    mesh->addTexture(defaultTexture);
    meshes.push_back(mesh);
  }

  Shader *billboardShader = new Shader("shaders/billboard.vert", "shaders/billboard.frag");
  billboardShader->setup();
  Texture *billboardTexture = new Texture("resources/default3.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
  billboardTexture->setup();
  billboardTexture->texUnit(billboardShader, "tex0", 0);

  std::cout << "billboardShader.ID: " << billboardShader->getId() << std::endl;

  Mesh *billboard = new Mesh(glm::vec3(5.0f, 8.0f, 0.0f), glm::vec3(0.0f), glm::vec3(1.0f), planeVertices, planeIndices, sizeof(planeVertices), sizeof(planeIndices), billboardShader);
  billboard->setup();
  billboard->setName("billboard");
  billboard->addTexture(billboardTexture);
  billboard->setIsBillboard(true);
  meshes.push_back(billboard);

  Shader *pointLightShader = new Shader("shaders/point_light.vert", "shaders/point_light.frag");
  pointLightShader->setup();
  Texture *pointLightTexture = new Texture("resources/point_light.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
  pointLightTexture->setup();
  pointLightTexture->texUnit(pointLightShader, "tex0", 0);

  Light *pointLight = new Light(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f), planeVertices, planeIndices, sizeof(planeVertices), sizeof(planeIndices), pointLightShader);
  pointLight->setup();
  pointLight->setName("point light");
  pointLight->addTexture(pointLightTexture);
  pointLight->setIsPointLight(true);
  pointLight->setLightSourceColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
  pointLightMeshes.push_back(pointLight);
  meshes.push_back(pointLight);

  Shader *pointLightShader2 = new Shader("shaders/point_light.vert", "shaders/point_light.frag");
  pointLightShader2->setup();
  Texture *pointLightTexture2 = new Texture("resources/point_light.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
  pointLightTexture2->setup();
  pointLightTexture2->texUnit(pointLightShader2, "tex0", 0);

  Light *pointLight2 = new Light(glm::vec3(4.0f, 4.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f), planeVertices, planeIndices, sizeof(planeVertices), sizeof(planeIndices), pointLightShader2);
  pointLight2->setup();
  pointLight2->setName("point light 2");
  pointLight2->addTexture(pointLightTexture2);
  pointLight2->setIsPointLight(true);
  pointLight2->setLightSourceColor(glm::vec4(1.0f, 0.0f, 1.0f, 1.0f));
  pointLightMeshes.push_back(pointLight2);
  meshes.push_back(pointLight2);
}

R1::Camera *R1::Scene::getCamera()
{
  return camera;
}

void R1::Scene::setScreenSize(int screenWidth, int screenHeight)
{
  this->screenWidth = screenWidth;
  this->screenHeight = screenHeight;
  camera->setScreenSize(screenWidth, screenHeight);
}

void R1::Scene::loop()
{
  if (!camera->getIsActiveCamera())
  {
    std::cout << "our main cam is not active" << std::endl;

    for (Mesh *mesh : meshes)
    {
      if (mesh->getIsCamera())
      {
        if (mesh->getCamera() && mesh->getCamera()->getIsActiveCamera())
        {
          camera = mesh->getCamera();
        }
      }
    }
  }

  if (camera->getMesh()->getIsCameraDeleted())
  {
    delete camera;
  }

  camera->handleInput(deltaTime);
  imgui->setMouseInteractions(camera->getIsMouseVisible());

  glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if (isVsyncEnabled)
  {
    glfwSwapInterval(1);
  }
  else
  {
    glfwSwapInterval(0);
  }

  for (Mesh *mesh : meshes)
  {
    if (mesh->getIsLightSource())
    {
      if (isLightMeshesVisible)
      {
        Light *light = dynamic_cast<Light *>(mesh);
        light->render(camera);
      }
    }
    else
    {
      mesh->render(camera, pointLightMeshes, &isLightsEnabled);
    }
    if (mesh->getIsSelected() && isDrawingLines)
    {
      glDisable(GL_DEPTH_TEST);
      xline->setPosition(mesh->getPosition());
      xline->setRotation(mesh->getRotation());
      xline->render(camera->getViewMatrix(), camera->getProjectionMatrix());

      yline->setPosition(mesh->getPosition());
      yline->setRotation(mesh->getRotation());
      yline->render(camera->getViewMatrix(), camera->getProjectionMatrix());

      zline->setPosition(mesh->getPosition());
      zline->setRotation(mesh->getRotation());
      zline->render(camera->getViewMatrix(), camera->getProjectionMatrix());
    }
  }

  if (isDrawingLines)
  {
    originXLine->render(camera->getViewMatrix(), camera->getProjectionMatrix());
    originYLine->render(camera->getViewMatrix(), camera->getProjectionMatrix());
    originZLine->render(camera->getViewMatrix(), camera->getProjectionMatrix());
  }

  currentFrame = glfwGetTime();
  deltaTime = currentFrame - previousFrame;
  previousFrame = currentFrame;
  fps = 1.0f / deltaTime;

  imgui->newFrame();
  imgui->drawGui();
  imgui->render();

  glfwSwapBuffers(window);
  glfwPollEvents();
}

void R1::Scene::cleanup()
{
  std::cout << "Scene::cleanup()" << std::endl;
  for (Mesh *mesh : meshes)
  {
    mesh->cleanup();
  }
  originXLine->cleanup();
  originYLine->cleanup();
  originZLine->cleanup();
  xline->cleanup();
  yline->cleanup();
  zline->cleanup();
  imgui->cleanup();
  camera->cleanup();
}