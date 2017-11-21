#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm\gtx/matrix_decompose.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <memory>

class Transform : std::enable_shared_from_this<Transform>
{
private:
	glm::mat4 _transform;

	glm::vec3 _scale;
	glm::quat _rotation;
	glm::vec3 _position;
	glm::vec3 _skew;
	glm::vec4 _perspective;

	std::vector<std::unique_ptr<Transform>> _children;
	std::shared_ptr<Transform> _parent;
public:
	Transform();
	Transform(const Transform & value);

	glm::mat4 getTransform();
	void setTransform(glm::mat4 transform);

	glm::vec3 getPosition();
	glm::vec3 getScale();
	glm::quat getRotation();

	std::vector<std::unique_ptr<Transform>>& getChildren();
	Transform& getParent();
	void setParent(Transform& parent);

	void rotate(float rad, glm::vec3 axis);
	void translate(glm::vec3 vec);
	void scale(glm::vec3 vec);

};

