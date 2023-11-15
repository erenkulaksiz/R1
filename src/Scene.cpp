#include <iostream>
#include <glad/glad.h>
#include <R1/Scene.h>
#include <R1/Camera.h>
#include <R1/Line.h>
#include <R1/Light.h>
#include <R1/ModelHandler.h>

GLfloat planeVertices[] =
    {
        //     COORDINATES     / TexCoord  /   normals
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, // Lower left corner
        -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,  // Upper left corner
        0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,   // Upper right corner
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,  // Lower right corner
};

GLuint planeIndices[] =
    {
        0, 2, 1,
        0, 3, 2};

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

  ModelHandler *skybox = new ModelHandler("D:/dosyalar/R1/src/resources/skybox.obj");
  std::vector<Mesh *> skyboxMesh = skybox->loadMeshes("D:/dosyalar/R1/src/shaders/skybox.vert", "D:/dosyalar/R1/src/shaders/skybox.frag");
  skyboxMesh[0]->setIsSkybox(true);
  skyboxMesh[0]->setScale(glm::vec3(20.0f));
  skyboxMesh[0]->setName("skybox");
  meshes.push_back(skyboxMesh[0]);

  ModelHandler *testCube = new ModelHandler("D:/dosyalar/R1/src/resources/cube_textured.obj");
  std::vector<Mesh *> testCubeMesh = testCube->loadMeshes("D:/dosyalar/R1/src/shaders/default_light.vert", "D:/dosyalar/R1/src/shaders/default_light.frag");
  testCubeMesh[0]->setName("test cube");
  meshes.push_back(testCubeMesh[0]);

  ModelHandler *testHome = new ModelHandler("D:/dosyalar/R1/src/resources/test_home.obj");
  std::vector<Mesh *> testHomeMesh = testHome->loadMeshes("D:/dosyalar/R1/src/shaders/default_light.vert", "D:/dosyalar/R1/src/shaders/default_light.frag");
  testHomeMesh[0]->setName("test home");
  meshes.push_back(testHomeMesh[0]);

  ModelHandler *testCube2 = new ModelHandler("D:/dosyalar/R1/src/resources/cube_textured.obj");
  std::vector<Mesh *> testCubeMesh2 = testCube2->loadMeshes("D:/dosyalar/R1/src/shaders/textured_w_skybox.vert", "D:/dosyalar/R1/src/shaders/textured_w_skybox.frag");
  testCubeMesh2[0]->setName("test cube 2 skyboxed");
  testCubeMesh2[0]->setPosition(glm::vec3(5.0f, 0.0f, 0.0f));
  meshes.push_back(testCubeMesh2[0]);

  ModelHandler *testCubeNormal = new ModelHandler("D:/dosyalar/R1/src/resources/wood_cube.obj");
  std::vector<Mesh *> testCubeNormalMesh = testCubeNormal->loadMeshes("D:/dosyalar/R1/src/shaders/default_light.vert", "D:/dosyalar/R1/src/shaders/default_light.frag");
  testCubeNormalMesh[0]->setName("normal cube");
  testCubeNormalMesh[0]->setPosition(glm::vec3(5.0f, 5.0f, 5.0f));
  meshes.push_back(testCubeNormalMesh[0]);

  Shader *billboardShader = new Shader("D:/dosyalar/R1/src/shaders/billboard.vert", "D:/dosyalar/R1/src/shaders/billboard.frag");
  billboardShader->setup();
  Texture *billboardTexture = new Texture("D:/dosyalar/R1/src/resources/default3.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE);
  billboardTexture->setup();
  billboardTexture->isDiffuse = true;
  billboardTexture->texUnit(billboardShader, "tex0", 0);

  Mesh *billboard = new Mesh(glm::vec3(5.0f, 8.0f, 0.0f), glm::vec3(0.0f), glm::vec3(1.0f), planeVertices, planeIndices, sizeof(planeVertices), sizeof(planeIndices), billboardShader);
  billboard->setName("billboard");
  billboard->addTexture(billboardTexture);
  billboard->setIsBillboard(true);
  billboard->setup();
  meshes.push_back(billboard);

  Shader *pointLightShader = new Shader("D:/dosyalar/R1/src/shaders/point_light.vert", "D:/dosyalar/R1/src/shaders/point_light.frag");
  pointLightShader->setup();
  Texture *pointLightTexture = new Texture("D:/dosyalar/R1/src/resources/point_light.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE);
  pointLightTexture->setup();
  pointLightTexture->isDiffuse = true;
  pointLightTexture->texUnit(pointLightShader, "tex0", 0);

  Light *pointLight = new Light(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f), planeVertices, planeIndices, sizeof(planeVertices), sizeof(planeIndices), pointLightShader);
  pointLight->setName("point light");
  pointLight->addTexture(pointLightTexture);
  pointLight->setIsPointLight(true);
  pointLight->setLightSourceColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
  pointLight->setup();
  pointLight->setIsVisible(false); // temp
  pointLightMeshes.push_back(pointLight);
  meshes.push_back(pointLight);

  Shader *pointLightShader2 = new Shader("D:/dosyalar/R1/src/shaders/point_light.vert", "D:/dosyalar/R1/src/shaders/point_light.frag");
  pointLightShader2->setup();
  Texture *pointLightTexture2 = new Texture("D:/dosyalar/R1/src/resources/point_light.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE);
  pointLightTexture2->setup();
  pointLightTexture2->isDiffuse = true;
  pointLightTexture2->texUnit(pointLightShader2, "tex0", 0);

  Light *pointLight2 = new Light(glm::vec3(4.0f, 4.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f), planeVertices, planeIndices, sizeof(planeVertices), sizeof(planeIndices), pointLightShader2);
  pointLight2->setName("point light 2");
  pointLight2->addTexture(pointLightTexture2);
  pointLight2->setIsPointLight(true);
  pointLight2->setLightSourceColor(glm::vec4(1.0f, 0.0f, 1.0f, 1.0f));
  pointLight2->setup();
  pointLight2->setIsVisible(false); // temp
  pointLightMeshes.push_back(pointLight2);
  meshes.push_back(pointLight2);

  Shader *directionalLightShader = new Shader("D:/dosyalar/R1/src/shaders/directional_light.vert", "D:/dosyalar/R1/src/shaders/directional_light.frag");
  directionalLightShader->setup();
  Texture *directionalLightTexture = new Texture("D:/dosyalar/R1/src/resources/directional_light.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE);
  directionalLightTexture->setup();
  directionalLightTexture->isDiffuse = true;
  directionalLightTexture->texUnit(directionalLightShader, "tex0", 0);

  Light *directionalLight = new Light(glm::vec3(0.0f, -4.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f), planeVertices, planeIndices, sizeof(planeVertices), sizeof(planeIndices), directionalLightShader);
  directionalLight->setName("directional light");
  directionalLight->addTexture(directionalLightTexture);
  directionalLight->setIsDirectionalLight(true);
  directionalLight->setLightSourceColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
  directionalLight->setup();
  directionalLightMeshes.push_back(directionalLight);
  meshes.push_back(directionalLight);

  /*
  ModelHandler *testPlane = new ModelHandler("resources/test_plane.obj");
  std::vector<Mesh *> testPlaneMesh = testPlane->loadMeshes();
  for (Mesh *mesh : testPlaneMesh)
  {
    mesh->setPosition(glm::vec3(5.0f, 5.0f, 0.0f));
    meshes.push_back(mesh);
  }

  ModelHandler *testPlane2 = new ModelHandler("resources/plane_test_3.fbx");
  std::vector<Mesh *> testPlaneMesh2 = testPlane2->loadMeshes();
  for (Mesh *mesh : testPlaneMesh2)
  {
    mesh->setPosition(glm::vec3(5.0f, -5.0f, 0.0f));
    mesh->setName("plane_test_3");
    meshes.push_back(mesh);
  }*/
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
      mesh->render(camera, pointLightMeshes, directionalLightMeshes, spotLightMeshes, &isLightsEnabled, &isGlobalWireframeEnabled);
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
    glDisable(GL_DEPTH_TEST);
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