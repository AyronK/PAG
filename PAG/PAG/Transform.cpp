#include "Transform.hpp"



Transform::Transform()
{
	transform = glm::mat4(1);
}


Transform::~Transform()
{
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
