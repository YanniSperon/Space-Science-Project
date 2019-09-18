#include "Player.h"

Player::Player()
	: Object(), Camera()
{

}

Player::Player(type type, std::string dir, std::string name, glm::vec3 rot, glm::vec3 trans, const std::string& texDir, const std::string& texName, bool canControl, float movementSpeed, glm::vec3 startingLookDirection, glm::vec3 startingUpDirection, glm::vec3 startingCameraTranslation, float mouseSensitivity)
	: Object(type, dir, name, rot, trans, texDir, texName), Camera(canControl, movementSpeed, startingLookDirection, startingUpDirection, startingCameraTranslation, mouseSensitivity)
{

}

Player::~Player()
{
}