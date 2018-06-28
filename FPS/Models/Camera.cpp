#include "Camera.h"
#include "../Managers/ResourceManager.h"

Camera::Camera(glm::vec3 position,glm::vec3 dir, glm::vec3 up, float yaw, float pitch):dir(dir),position(position),worldUp(up),yaw(yaw),pitch(pitch),movementSpeed(SPEED),mouseSensitivity(SENSITIVITY)
{
	btCollisionShape* cameraShape = new btBoxShape(btVector3(1.25, 0.5, 1.25));
	btDefaultMotionState* cameraMotionState =
                new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(8, 1, 50)));
	btScalar mass = 1;
	btVector3 cameraInertia(0, 0, 0);
	cameraShape->calculateLocalInertia(mass, cameraInertia);
	btRigidBody::btRigidBodyConstructionInfo cameraRigidBodyCI(mass, cameraMotionState, cameraShape, cameraInertia);
	cameraRigidBody = new btRigidBody(cameraRigidBodyCI);
	ResourceManager::getResourceManager().dynamicsWorld->addRigidBody(cameraRigidBody);
	
	updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix()
{
	return glm::lookAt(position, position + dir, up);
}

void Camera::processMovement(int direction, float deltaTime)
{	
	auto btDir = btVector3(dir.x, 0, dir.z);
	auto btRight = btVector3(right.x, right.y, right.z);
	glm::vec3 velocity = glm::vec3(0, 0, 0); //movementSpeed * deltaTime;
	
	cameraRigidBody->activate(true);
	if (direction & FORWARD)
		velocity += dir;
	//	cameraRigidBody->setLinearVelocity(btDir.normalize()*movementSpeed);
	//	cameraRigidBody->translate(btDir * velocity);
	if (direction & BACKWARD)
		velocity -= dir;
	//	cameraRigidBody->setLinearVelocity(btDir.normalize()*movementSpeed*(-1));
	//	cameraRigidBody->translate(btDir * velocity * (-1));	
	if (direction & LEFT)
		velocity -= right;
	//cameraRigidBody->setLinearVelocity(btRight.normalize()*movementSpeed*(-1));
	//	cameraRigidBody->translate(btRight * velocity * (-1));
	if (direction & RIGHT)
		velocity += right;
	//	cameraRigidBody->setLinearVelocity(btRight.normalize()*movementSpeed);
	//	cameraRigidBody->translate(btRight * velocity);
	velocity.y = 0;
	float y = cameraRigidBody->getLinearVelocity().y();
	if (velocity.x != 0 || velocity.z != 0) {
		velocity = glm::normalize(velocity);
		velocity *=movementSpeed;
		
		cameraRigidBody->setLinearVelocity(btVector3(velocity.x, y, velocity.z));
	}
	else cameraRigidBody->setLinearVelocity(btVector3(0, y, 0));
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

glm::vec3 Camera::getPosition() {
	btVector3 &vec = cameraRigidBody->getWorldTransform().getOrigin();
	return glm::vec3(vec.x(), vec.y(), vec.z());
}