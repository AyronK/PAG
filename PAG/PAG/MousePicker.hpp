#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.hpp"
#include <memory>
#include <vector>

class Node;
class Model;
class Scene;

class MousePicker
{
private:
	glm::vec3 currentRay;
	glm::mat4 projectionMatrix;
	glm::mat3 viewMatrix;
	std::shared_ptr<Camera> camera;
	glm::vec3 calculateMouseRay(float mouseX, float mouseY);
public:
	glm::vec3 getCurrentRay();
	void update(float mouseX, float mouseY);
	MousePicker();
	MousePicker(Camera& camera, glm::mat4 projection);
	~MousePicker();
	glm::vec3 getPointOnRay(glm::vec3 ray, float distance);
	Node * getSelectedNode(Scene * const pScene, std::vector<Model*>, const std::pair<int, int>& pScreenSize, const std::pair<double, double>& pMousePos);
	static const bool checkRayIntersectionTriangle(const glm::vec3 & pRaySource, const glm::vec3 & pRayDirection, const glm::vec3 triangle[3], float & pDistanceOutput);
	};

