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
public:
	MousePicker();
	~MousePicker();
	Node * getSelectedNode(Scene * const pScene, std::vector<Model*>, const std::pair<int, int>& pScreenSize, const std::pair<double, double>& pMousePos);
	static const bool checkRayIntersectionTriangle(const glm::vec3 & pRaySource, const glm::vec3 & pRayDirection, const glm::vec3 triangle[3], float & pDistanceOutput);
};

