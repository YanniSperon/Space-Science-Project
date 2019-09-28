#pragma once

#include "glm/glm.hpp"
#include "Object.h"

class Camera {
public:
	bool hasControls;
	bool isFollowing;
	float movementSpeed;
	glm::vec3 viewDirection;
	glm::vec3 upDirection;
	glm::vec3 cameraTranslation;
	double oldMouseX;
	double oldMouseY;
	float mouseSensitivity;
public:
	Camera();
	Camera(bool canControl, float movementSpeed, glm::vec3 startingLookDirection, glm::vec3 startingUpDirection, glm::vec3 startingCameraTranslation, float mouseSensitivity);
	~Camera();
	void EnableMovementControls();
	void DisableMovementControls();
	glm::mat4 GetViewTransformMatrix();
	glm::vec3 GetTranslation();
	void LookAt(double xpos, double ypos);
	void MoveForward(float deltaT);
	void MoveBackward(float deltaT);
	void StrafeLeft(Object& obj, float deltaT);
	void StrafeRight(Object& obj, float deltaT);
	void MoveUp(float deltaT);
	void MoveDown(float deltaT);
	void ChangeMovementSpeed(float newSpeed);

	void BringWith(Object& obj);
	void Follow(Object& obj);
	void Unfollow();
};