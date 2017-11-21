#include "Scene.hpp"
#include "Shader.hpp"
#include "Camera.hpp"

Scene::Scene()
{
	projectionSpace = glm::perspective(glm::radians(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
}

glm::mat4 Scene::getViewSpace() { return viewSpace; }
glm::mat4 Scene::getProjectionSpace() { return projectionSpace; }

void Scene::updateViewSpace(Camera& camera)
{
	viewSpace = glm::lookAt(camera.cameraPos, camera.cameraPos + camera.cameraFront, camera.cameraUp);
}

Scene::~Scene() {}