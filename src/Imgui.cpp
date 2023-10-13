#include <glad/glad.h>
#include <iostream>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <R1/Imgui.h>
#include <R1/Camera.h>
#include <R1/Scene.h>

R1::Imgui::Imgui()
{
  std::cout << "Imgui::Imgui()" << std::endl;
}

void R1::Imgui::setup()
{
  std::cout << "Imgui::setup()" << std::endl;
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  (void)io;
  ImGui::StyleColorsDark();
  ImGui_ImplGlfw_InitForOpenGL(glfwGetCurrentContext(), true);
  ImGui_ImplOpenGL3_Init("#version 330");
}

void R1::Imgui::setScene(Scene *scene)
{
  this->scene = scene;
}

void R1::Imgui::newFrame()
{
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
}

void R1::Imgui::render()
{
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void R1::Imgui::setMouseInteractions(bool value)
{
  mouseInteractions = value;
  if (mouseInteractions == false)
  {
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NoMouse;
  }
  else
  {
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags &= ~ImGuiConfigFlags_NoMouse;
  }
}

void R1::Imgui::drawGui()
{
  ImGui::SetNextWindowPos(ImVec2(0, 0));
  ImGui::Begin("scene");

  if (ImGui::Button(scene->isPlaying ? "stop" : "play"))
  {
    scene->isPlaying = !scene->isPlaying;
  }

  if (ImGui::CollapsingHeader("editor"))
  {
    ImGui::Checkbox("draw lines", &scene->isDrawingLines);
    ImGui::Checkbox("show light meshes", &scene->isLightMeshesVisible);
    ImGui::Checkbox("vsync", &scene->isVsyncEnabled);
    ImGui::Checkbox("lights", &scene->isLightsEnabled);
  }

  if (ImGui::CollapsingHeader("statistics"))
  {
    ImGui::Text("fps: %f", scene->fps);
    ImGui::Text("deltaTime: %f", scene->deltaTime * 1000.0f);
    ImGui::Text("meshes: %d", scene->meshes.size());
  }

  if (ImGui::CollapsingHeader("world"))
  {
    static bool glLineRenderer = false;
    ImGui::Checkbox("wireframe", &glLineRenderer);
    static float backgroundColor[3] = {scene->backgroundColor.r, scene->backgroundColor.g, scene->backgroundColor.b};
    if (ImGui::ColorEdit3("background", backgroundColor))
    {
      scene->backgroundColor = glm::vec4(backgroundColor[0], backgroundColor[1], backgroundColor[2], 1.0f);
    }
    if (glLineRenderer)
    {
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else
    {
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    if (ImGui::BeginListBox("##world", ImVec2(-FLT_MIN, 5 * ImGui::GetTextLineHeightWithSpacing())))
    {
      for (int i = 0; i < scene->meshes.size(); i++)
      {
        const bool is_selected = (selectedMeshIndex == i);
        if (ImGui::Selectable(scene->meshes[i]->getName().c_str(), is_selected))
        {
          if (selectedMeshIndex == i)
          {
            selectedMeshIndex = -1;
          }
          else
          {
            selectedMeshIndex = i;
          }
        }

        if (is_selected && selectedMeshIndex != -1)
        {
          ImGui::SetItemDefaultFocus();
          glm::vec3 currentPosition = scene->meshes[selectedMeshIndex]->getPosition();
          glm::vec3 currentRotation = scene->meshes[selectedMeshIndex]->getRotation();
          glm::vec3 currentScale = scene->meshes[selectedMeshIndex]->getScale();
          positionVec3[0] = currentPosition.x;
          positionVec3[1] = currentPosition.y;
          positionVec3[2] = currentPosition.z;
          rotationVec3[0] = currentRotation.x;
          rotationVec3[1] = currentRotation.y;
          rotationVec3[2] = currentRotation.z;
          scaleVec3[0] = currentScale.x;
          scaleVec3[1] = currentScale.y;
          scaleVec3[2] = currentScale.z;
          scene->meshes[i]->setIsSelected(true);
        }
        else
        {
          if (scene->meshes[i]->getIsSelected())
          {
            scene->meshes[i]->setIsSelected(false);
          }
        }
      }
      ImGui::EndListBox();
    }
    if (ImGui::Button("add"))
    {
    }
  }
  ImGui::End();

  if (selectedMeshIndex != -1)
  {
    ImGui::Begin("inspector");

    if (scene->meshes[selectedMeshIndex]->getIsCamera())
    {
      if (!scene->meshes[selectedMeshIndex]->getCamera()->getIsActiveCamera())
      {
        if (ImGui::Button("delete"))
        {
          scene->meshes[selectedMeshIndex]->deleteCamera();
          scene->meshes.erase(scene->meshes.begin() + selectedMeshIndex);
          selectedMeshIndex = -1;
          ImGui::End();
          return;
        }
      }
    }
    else
    {
      if (ImGui::Button("delete"))
      {
        scene->meshes[selectedMeshIndex]->cleanup();
        scene->meshes.erase(scene->meshes.begin() + selectedMeshIndex);
        selectedMeshIndex = -1;
        ImGui::End();
        return;
      }
    }

    if (scene->meshes[selectedMeshIndex]->getIsCamera())
    {
      if (!scene->meshes[selectedMeshIndex]->getCamera()->getIsActiveCamera())
      {
        ImGui::SameLine();
        if (ImGui::Button("set active camera"))
        {
          for (int i = 0; i < scene->meshes.size(); i++)
          {
            if (scene->meshes[i]->getIsCamera() && scene->meshes[i]->getCamera()->getIsActiveCamera())
            {
              scene->meshes[i]->getCamera()->setIsActiveCamera(false);
            }
          }
          scene->meshes[selectedMeshIndex]->getCamera()->setIsActiveCamera(true);
        }
      }
      else
      {
        ImGui::SameLine();
        ImGui::Text("active camera");
      }
    }

    ImGui::SeparatorText("general");

    if (!scene->meshes[selectedMeshIndex]->getIsCamera())
    {
      bool isVisible = scene->meshes[selectedMeshIndex]->getIsVisible();
      if (ImGui::Checkbox("visible", &isVisible))
      {
        scene->meshes[selectedMeshIndex]->setIsVisible(isVisible);
      }
    }

    char meshName[128];
    strcpy(meshName, scene->meshes[selectedMeshIndex]->getName().c_str());
    if (ImGui::InputText("name", meshName, sizeof(meshName)))
    {
      scene->meshes[selectedMeshIndex]->setName(meshName);
    }

    if (ImGui::CollapsingHeader("transform"))
    {
      if (ImGui::DragFloat3("position", positionVec3, 0.1f, -1000.0f, 1000.0f, "%.1f"))
      {
        scene->meshes[selectedMeshIndex]->setPosition(glm::vec3(positionVec3[0], positionVec3[1], positionVec3[2]));
      }
      if (ImGui::DragFloat3("rotation", rotationVec3, 0.1f, -1000.0f, 1000.0f, "%.1f"))
      {
        if (rotationVec3[0] >= 360.0f)
        {
          rotationVec3[0] = 0.0f;
        }
        else if (rotationVec3[0] < 0.0f)
        {
          rotationVec3[0] = 360.0f;
        }

        if (rotationVec3[1] >= 360.0f)
        {
          rotationVec3[1] = 0.0f;
        }
        else if (rotationVec3[1] < 0.0f)
        {
          rotationVec3[1] = 360.0f;
        }

        if (rotationVec3[2] >= 360.0f)
        {
          rotationVec3[2] = 0.0f;
        }
        else if (rotationVec3[2] < 0.0f)
        {
          rotationVec3[2] = 360.0f;
        }

        scene->meshes[selectedMeshIndex]->setRotation(glm::vec3(rotationVec3[0], rotationVec3[1], rotationVec3[2]));
      }
      if (ImGui::DragFloat3("scale", scaleVec3, 0.1f, -1000.0f, 1000.0f, "%.1f"))
      {
        scene->meshes[selectedMeshIndex]->setScale(glm::vec3(scaleVec3[0], scaleVec3[1], scaleVec3[2]));
      }
    }

    Light *light = dynamic_cast<Light *>(scene->meshes[selectedMeshIndex]);

    if (light)
    {
      if (light->getIsLightSource())
      {
        if (ImGui::CollapsingHeader("light"))
        {
          ImVec4 lightColor = ImVec4(light->getLightSourceColor().x,
                                     light->getLightSourceColor().y,
                                     light->getLightSourceColor().z,
                                     light->getLightSourceColor().w);
          if (ImGui::ColorEdit4("color", &lightColor.x))
          {
            light->setLightSourceColor(glm::vec4(lightColor.x, lightColor.y, lightColor.z, lightColor.w));
          }
          float intensity = light->getLightSourceIntensity();
          if (ImGui::DragFloat("intensity", &intensity, 0.01f, 0.0f, 50.0f))
          {
            light->setLightSourceIntensity(intensity);
          }
          if (light->getIsPointLight())
          {
            if (ImGui::CollapsingHeader("point light"))
            {
              glm::vec3 ambient = light->getLightSourceAmbient();
              if (ImGui::DragFloat("ambient", &ambient.x, 0.01f, 0.0f, 50.0f))
              {
                light->setLightSourceAmbient(ambient);
              }
              glm::vec3 diffuse = light->getLightSourceDiffuse();
              if (ImGui::DragFloat("diffuse", &diffuse.x, 0.01f, 0.0f, 50.0f))
              {
                light->setLightSourceDiffuse(diffuse);
              }
              glm::vec3 specular = light->getLightSourceSpecular();
              if (ImGui::DragFloat("specular", &specular.x, 0.01f, 0.0f, 50.0f))
              {
                light->setLightSourceSpecular(specular);
              }
              float constant = light->getLightSourceConstant();
              if (ImGui::DragFloat("constant", &constant, 0.01f, 0.0f, 50.0f))
              {
                light->setLightSourceConstant(constant);
              }
              float linear = light->getLightSourceLinear();
              if (ImGui::DragFloat("linear", &linear, 0.001f, 0.0f, 50.0f))
              {
                light->setLightSourceLinear(linear);
              }
              float quadratic = light->getLightSourceQuadratic();
              if (ImGui::DragFloat("quadratic", &quadratic, 0.001f, 0.0f, 50.0f))
              {
                light->setLightSourceQuadratic(quadratic);
              }
            }
          }
        }
      }
    }

    if (scene->meshes[selectedMeshIndex]->getIsCamera())
    {
      if (ImGui::CollapsingHeader("camera"))
      {
        float fov = scene->meshes[selectedMeshIndex]->getCamera()->getFov();
        if (ImGui::DragFloat("fov", &fov, 0.1f, 30.0f, 180.0f))
        {
          scene->meshes[selectedMeshIndex]->getCamera()->setFov(fov);
        }
      }
    }

    if (scene->meshes[selectedMeshIndex]->getIsTextured())
    {
      if (ImGui::CollapsingHeader("textures"))
      {
        std::vector<R1::Texture *> textures = scene->meshes[selectedMeshIndex]->getTextures();
        for (Texture *texture : textures)
        {
          ImGui::Image((void *)(intptr_t)texture->ID, ImVec2(64, 64));
          ImGui::SameLine();
          ImGui::Text(texture->image);
        }
      }
    }

    ImGui::End();
  }
}

void R1::Imgui::cleanup()
{
  std::cout << "Imgui::cleanup()" << std::endl;
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
}