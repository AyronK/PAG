#include "MousePicker.hpp"
#include <GLFW/glfw3.h>

glm::vec3 MousePicker::calculateMouseRay(float mouseX, float mouseY)
{
	float x = (2.0f*mouseX) / SCREEN_WIDTH - 1.0f;
	float y = (2.0f*mouseY) / SCREEN_HEIGHT - 1.0f;

	glm::vec4 clipCoords = glm::vec4(x, y, -1.0f, 1.0f);

	glm::mat4 inversedProjection = glm::inverse(projectionMatrix);
	glm::vec4 eyeCoords = inversedProjection * clipCoords;

	glm::mat4 inversedView = glm::inverse(viewMatrix);
	glm::vec4 rayWorld = inversedView * eyeCoords;
	glm::vec3 worldRay = glm::vec3(rayWorld.x, rayWorld.y, rayWorld.z);
	worldRay = glm::normalize(worldRay);
	return worldRay;
}

glm::vec3 MousePicker::getCurrentRay()
{
	return currentRay;
}

void MousePicker::update(float mouseX, float mouseY)
{
	this->viewMatrix = camera->getViewMatrix();
	currentRay = calculateMouseRay(mouseX, mouseY);
}

MousePicker::MousePicker()
{
}

MousePicker::MousePicker(Camera& camera, glm::mat4 projection)
{
	this->camera = std::make_shared<Camera>(camera);
	this->projectionMatrix = projection;
	this->viewMatrix = camera.getViewMatrix();
}


MousePicker::~MousePicker()
{
}
