#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
class Transform
{
public:
	glm::mat4 transform;
	//std::vector<Transform> children;
	Transform();
	~Transform();
	void rotate(float rad, glm::vec3 axis);
	void translate(glm::vec3 vec);
	void scale(glm::vec3 vec);
};

