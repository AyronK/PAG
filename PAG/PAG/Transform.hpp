#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <memory>
#include <assimp/matrix4x4.h>

class Transform : public std::enable_shared_from_this<Transform>
{
private:
	glm::mat4 _transform;

	glm::vec3 _scale;
	glm::quat _rotation;
	glm::vec3 _position;
	glm::vec3 _skew;
	glm::vec4 _perspective;

	glm::vec3 _rotationAxis = glm::vec3(1.0f, 0, 0);
	float _rotationAngle = 0.0f;

	void update();
public:
	Transform();
	Transform(const Transform & value);

	void importAiTransform(aiMatrix4x4 pMatrix);
	glm::mat4 getTransform();
	void setTransform(glm::mat4 transform);


	glm::vec3 getPosition();
	glm::vec3 getScale();
	glm::quat getRotation();


	void setPosition(glm::vec3 position);
	const std::pair<glm::vec3, float> getRotationAxisAndAngle();
	void setScale(glm::vec3 rotation);
	void setRotation(float rad, glm::vec3 axis);

	void rotate(float rad, glm::vec3 axis);
	void translate(glm::vec3 vec);
	void scale(glm::vec3 vec);

};

