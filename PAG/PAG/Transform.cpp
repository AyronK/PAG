#include "Transform.hpp"


#pragma region Constructors/Destructors
Transform::Transform()
{
	_transform = glm::mat4(1);
	_parent = std::shared_ptr<Transform>();
}

Transform::Transform(const Transform &) { Transform(); }

Transform::~Transform() {}
#pragma endregion

#pragma region Getters/Setters
glm::mat4 Transform::getTransform()
{
	return _transform;
}

void Transform::setTransform(glm::mat4 transform)
{
	this->_transform = transform;
	glm::decompose(transform, _scale, _rotation, _position, _skew, _perspective);
}

glm::vec3 Transform::getPosition() {
	return _position;
}

glm::vec3 Transform::getScale()
{
	return _scale;
}

glm::quat Transform::getRotation()
{
	return _rotation;
}

std::vector<std::shared_ptr<Transform>>& Transform::getChildren()
{
	return _children;
}

Transform& Transform::getParent()
{
	return *_parent;
}

void Transform::setParent(Transform& parent)
{
	_parent = std::shared_ptr<Transform>(&parent);
	parent.getChildren().push_back(std::shared_ptr<Transform>(this));
}
#pragma endregion

void Transform::rotate(float rad, glm::vec3 axis)
{
	setTransform(glm::rotate(_transform, rad, axis));
}

void Transform::translate(glm::vec3 vec)
{
	setTransform(glm::translate(_transform, vec));
}

void Transform::scale(glm::vec3 vec)
{
	setTransform(glm::scale(_transform, vec));
}
