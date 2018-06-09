#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};
// Default camera values
const double YAW = -90.0f;
const double PITCH = 0.0f;
const double SPEED = 2.5f;
const double SENSITIVITY = 0.1f;
const double ZOOM = 45.0f;
struct Camera {

	glm::vec3 position;
	glm::vec3 dir;
	glm::vec3 up;
	
	glm::vec3 right;
	glm::vec3 worldUp;
	double yaw;
	double pitch;

	double movementSpeed;
	double mouseSensitivity;

	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 dir = glm::vec3(0,0,1), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),  float yaw = YAW, float pitch = PITCH);
	glm::mat4 getViewMatrix();
	void processMovement(Camera_Movement direction, float deltaTime);
	void processMouse(double xoffset, double toffset, bool constraintPitch = true);

	void updateCameraVectors();


};