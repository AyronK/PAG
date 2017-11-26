#include "Transform.hpp"

#pragma region Constructors/Destructors
Transform::Transform()
{
	setTransform(glm::mat4(1));
	_parent = std::shared_ptr<Transform>();
	sharedPtrOfThis = std::make_shared<Transform>(*this);
}

Transform::Transform(const Transform & value)
{
	setTransform(value._transform);
	_parent = value._parent;
}
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
	_parent.reset(&parent);
	parent.getChildren().push_back(std::make_shared<Transform>(*this));
}
#pragma endregion

void Transform::rotate(float rad, glm::vec3 axis)
{
	setTransform(glm::rotate(_transform, rad, axis));
    for (auto child: _children)
	{
		child->rotate(rad, axis);
	}
}

void Transform::translate(glm::vec3 translation)
{
	setTransform(glm::translate(_transform, translation));
    for (auto child: _children)
	{
		child->translate(translation);
	}
}

void Transform::scale(glm::vec3 scale)
{
	setTransform(glm::scale(_transform, scale));
    /*for (auto child: _children)
	{
		child->scale(scale);
	}*/
}
