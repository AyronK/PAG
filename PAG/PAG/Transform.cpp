#include "Transform.hpp"



Transform::Transform()
{
	transform = glm::mat4(1);
}


Transform::~Transform()
{
}

glm::vec3 Transform::getPosition() {
	glm::mat4 transformation = transform; // your transformation matrix.
	glm::vec3 scale;
	glm::quat rotation;
	glm::vec3 translation;
	glm::vec3 skew;
	glm::vec4 perspective;
	glm::decompose(transformation, scale, rotation, translation, skew, perspective);
	return translation;
}

void Transform::rotate(float rad, glm::vec3 axis)
{
	transform = glm::rotate(transform, rad, axis);
}

void Transform::translate(glm::vec3 vec)
{
	transform = glm::translate(transform, vec);
}

void Transform::scale(glm::vec3 vec)
{
	transform = glm::scale(transform, vec);
}
