#pragma once
#include "Object.h"
#include "Camera.h"

class Player : public Object, public Camera {
private:
public:
	Player();
	Player(type type, std::string dir, std::string name, glm::vec3 rot, glm::vec3 trans, const std::string& texDir, const std::string& texName, bool canControl, float movementSpeed, glm::vec3 startingLookDirection, glm::vec3 startingUpDirection, glm::vec3 startingCameraTranslation, float mouseSensitivity);

	~Player();
};