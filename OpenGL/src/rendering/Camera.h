#pragma once

#include "glm/glm.hpp"
#include "Object.h"

class Camera {
public:
	bool hasControls;
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
	void LookAt(double xpos, double ypos);
	void MoveForward();
	void MoveBackward();
	void StrafeLeft();
	void StrafeRight();
	void MoveUp();
	void MoveDown();
	void ChangeMovementSpeed(float newSpeed);

	void BringWith(Object& obj);
};