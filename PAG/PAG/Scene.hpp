#include "Transform.hpp"
#include <vector>
#pragma once
class Scene
{

public:
	std::vector<Transform> hierarchy;
	Scene();
	~Scene();
};

