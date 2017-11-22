#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "config.hpp"
class Camera
{
private:
    void updateCameraVectors();

public:
	Camera();
	~Camera();

	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;

	glm::mat4 getViewMatrix();

	bool firstMouse;
	float yaw;	
	float pitch;
	double lastX;
	double lastY;
	float fov;

    void rotateByOffset(float pOffsetX, float pOffsetY);
};

