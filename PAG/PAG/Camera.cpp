#include "Camera.hpp"

Camera::Camera()
{
	bool firstMouse = true;
	yaw = 270.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
	pitch = 0.0f;
	lastX = SCREEN_WIDTH / 2.0f;
	lastY = SCREEN_HEIGHT / 2.0f;
	fov = 45.0f;

	cameraPos = glm::vec3(0.0f, 0.0f, 25.0f);  // camera position in world space
	cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);  // vector "up
	updateCameraVectors();
}

Camera::~Camera()
{

}


void Camera::rotateByOffset(float pOffsetX, float pOffsetY)
{
	pitch += pOffsetY;
	yaw += pOffsetX;
	if (pitch > 89.0f)
		pitch = 89.0f;
	else if (pitch < -89.0f)
		pitch = -89.0f;
	updateCameraVectors();
}

void Camera::updateCameraVectors()
{
	glm::vec3 newFront;
	newFront.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	newFront.y = sin(glm::radians(pitch));
	newFront.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
	cameraFront = glm::normalize(newFront);
	//cameraPos = glm::normalize(glm::cross(cameraFront, cameraUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	//cameraUp = glm::normalize(glm::cross(cameraPos, cameraFront));
}