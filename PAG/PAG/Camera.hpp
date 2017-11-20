#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "config.hpp"
class Camera
{
private:
	void Camera::updateCameraVectors();

public:
	Camera();
	~Camera();

	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;

	bool firstMouse;
	float yaw;	
	float pitch;
	double lastX;
	double lastY;
	float fov;

	void Camera::rotateByOffset(float pOffsetX, float pOffsetY);
};

