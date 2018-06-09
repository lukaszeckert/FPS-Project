#include "Camera.h"

Camera::Camera(glm::vec3 position,glm::vec3 dir, glm::vec3 up, float yaw, float pitch):dir(dir),position(position),worldUp(up),yaw(yaw),pitch(pitch),movementSpeed(SPEED),mouseSensitivity(SENSITIVITY)
{
	updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix()
{
	return glm::lookAt(position, position + dir, up);
}

void Camera::processMovement(Camera_Movement direction, float deltaTime)
{
	
	float velocity = movementSpeed * deltaTime;
	if (direction == FORWARD)
		position += dir * velocity;
	if (direction == BACKWARD)
		position -= dir * velocity;
	if (direction == LEFT)
		position -= right * velocity;
	if (direction == RIGHT)
		position += right * velocity;
	updateCameraVectors();
}

void Camera::processMouse(double xoffset, double yoffset, bool constrainPitch)
{
	xoffset *= mouseSensitivity;
	yoffset *= mouseSensitivity;

	yaw += xoffset;
	pitch += yoffset;

	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (constrainPitch)
	{
		if (pitch > 89.0f)
				pitch = 89.0f;
		if (pitch < -89.0f)
				pitch = -89.0f;
	}

	// Update Front, Right and Up Vectors using the updated Euler angles
	updateCameraVectors();
	
}

void Camera::updateCameraVectors()
{
	// Calculate the new Front vector
	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	dir = glm::normalize(front);
	// Also re-calculate the Right and Up vector
	right = glm::normalize(glm::cross(dir, worldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	up = glm::normalize(glm::cross(right, dir));
}
