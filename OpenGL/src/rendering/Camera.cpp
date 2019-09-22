#include "Camera.h"
#include "Config.h"
#include "glm/gtc/matrix_transform.hpp"
#include <iostream>

Camera::Camera()
	: hasControls(false), movementSpeed(0.1f), viewDirection(0.0f, 0.0f, -1.0f), upDirection(0.0f, 1.0f, 0.0f), cameraTranslation(0.0f, 0.0f, 0.0f), oldMouseX(0.0), oldMouseY(0.0), mouseSensitivity(0.0f), isFollowing(false)
{
	
}

Camera::Camera(bool canControl, float movementSpeed, glm::vec3 startingLookDirection, glm::vec3 startingUpDirection, glm::vec3 startingCameraTranslation, float mouseSensitivity)
	: hasControls(canControl), movementSpeed(movementSpeed), viewDirection(startingLookDirection), upDirection(startingUpDirection), 
	cameraTranslation(startingCameraTranslation), oldMouseX(0.0), oldMouseY(0.0), mouseSensitivity(mouseSensitivity), isFollowing(false)
{

}

Camera::~Camera()
{

}

void Camera::EnableMovementControls()
{
	hasControls = true;
}

void Camera::DisableMovementControls()
{
	hasControls = false;
}

glm::mat4 Camera::GetViewTransformMatrix()
{
	return glm::lookAt(cameraTranslation, cameraTranslation + viewDirection, upDirection);
}

glm::vec3 Camera::GetTranslation()
{
	return cameraTranslation;
}

void Camera::LookAt(double xpos, double ypos)
{
	//if (hasControls) {
	//	glm::vec2 mouseDelta(xpos - oldMouseX, ypos - oldMouseY);

	//	// finds the vector perpendicular to both viewDirection and upDirection to find which axis to rotate  the camera around.
	//	glm::vec3 toRotateAround = glm::cross(viewDirection, upDirection);
	//	glm::vec3 vd;
	//	viewDirection = glm::mat3(
	//		glm::rotate(glm::mat4(1.0f), -mouseDelta.x * mouseSensitivity, upDirection) *
	//		glm::rotate(glm::mat4(1.0f), -mouseDelta.y * mouseSensitivity, toRotateAround)
	//	) * viewDirection;

	//	viewDirection = glm::mat3() * viewDirection;

	//	oldMouseX = xpos;
	//	oldMouseY = ypos;
	//}
}

void Camera::MoveForward()
{
	if (hasControls) {
		if (cameraTranslation.z > 1.75f) {
			cameraTranslation.z += -movementSpeed;
		}
	}
}

void Camera::MoveBackward()
{
	if (hasControls) {
		if (cameraTranslation.z < 10.0f) {
			cameraTranslation.z += movementSpeed;
		}
	}
}

void Camera::StrafeLeft(Object& obj)
{
	if (hasControls) {
		if (!isFollowing) {
			cameraTranslation.x += -movementSpeed;
		}
		else {
			obj.TranslateSubtract3f(movementSpeed, 0.0f, 0.0f);
		}
	}
}

void Camera::StrafeRight(Object& obj)
{
	if (hasControls) {
		if (!isFollowing) {
			cameraTranslation.x += movementSpeed;
		}
		else {
			obj.TranslateAdd3f(movementSpeed, 0.0f, 0.0f);
		}
	}
}

void Camera::MoveUp()
{
	if (hasControls) {
		cameraTranslation.y += movementSpeed;
	}
}

void Camera::MoveDown()
{
	if (hasControls) {
		cameraTranslation.y += -movementSpeed;
	}
}

void Camera::ChangeMovementSpeed(float newSpeed)
{
	movementSpeed = newSpeed;
}

void Camera::StickToView(Object& obj)
{
	glm::vec3 originalPosition = obj.GetTranslation();
	obj.Translate3f(originalPosition.x, originalPosition.y, cameraTranslation.z + 0.11f);
}

void Camera::BringWith(Object& obj)
{
	glm::vec3 originalPosition = obj.GetTranslation();
	obj.Translate3f(cameraTranslation.x, cameraTranslation.y, originalPosition.z);
}

void Camera::Follow(Object& obj)
{
	glm::vec3 objPosition = obj.GetTranslation();
	cameraTranslation.x = objPosition.x;
	cameraTranslation.y = objPosition.y;
	isFollowing = true;
}

void Camera::Unfollow()
{
	isFollowing = false;
}
