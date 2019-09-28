#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>

#include "Shader.h"
#include "Mesh.h"
#include "Camera.h"
#include "Config.h"
#include "Object.h"
#include "Player.h"
#include "BoundingSphere.h"
#include "IntersectData.h"
#include "Plane.h"
#include "Sprite.h"
#include "SpritePhysicsBody.h"
#include "Timer.h"
#include "CollidableSprite.h"
#include "Simple2DRenderer.h"
#include "Vertex.h"
#include "ShapeGenerator.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/euler_angles.hpp"
#include "glm/gtx/quaternion.hpp"
#include "stb_image/stb_image.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"

Config config = Config("res/other/", "config.txt");

static bool fullscreen = config.getFullscreenPreference();
static float mouseSensitivity = config.getMouseSensitivityPreference();
static float FOV = config.getFOVPreference();

static bool wPressed = false;
static bool sPressed = false;
static bool aPressed = false;
static bool dPressed = false;
static bool spacePressed = false;
static bool controlPressed = false;
static bool shiftPressed = false;
static bool tPressed = false;
static bool leftClicked = false;
static bool rightClicked = false;

static int oldMouseX = 0;
static int oldMouseY = 0;
static float movementSpeed = 0.05f;
static float shootSpeed = 5.0f;

float cursorXPos = 0.0;
float cursorYPos = 0.0;

Camera camera = Camera(true, movementSpeed, glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 5.0f), mouseSensitivity);

static int initialWidth = config.getInitialWidthPreference();
static int initialHeight = config.getInitialHeightPreference();

static int currentWidth = initialWidth;
static int currentHeight = initialHeight;



static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if ((key == GLFW_KEY_W || key == GLFW_KEY_UP) && action == GLFW_PRESS) {
		wPressed = true;
	}
	else if ((key == GLFW_KEY_W || key == GLFW_KEY_UP) && action == GLFW_RELEASE) {
		wPressed = false;
	}

	if ((key == GLFW_KEY_S || key == GLFW_KEY_DOWN) && action == GLFW_PRESS) {
		sPressed = true;
	}
	else if ((key == GLFW_KEY_S || key == GLFW_KEY_DOWN) && action == GLFW_RELEASE) {
		sPressed = false;
	}



	if ((key == GLFW_KEY_A || key == GLFW_KEY_LEFT) && action == GLFW_PRESS) {
		aPressed = true;
	}
	else if ((key == GLFW_KEY_A || key == GLFW_KEY_LEFT) && action == GLFW_RELEASE) {
		aPressed = false;
	}

	if ((key == GLFW_KEY_D || key == GLFW_KEY_RIGHT) && action == GLFW_PRESS) {
		dPressed = true;
	}
	else if ((key == GLFW_KEY_D || key == GLFW_KEY_RIGHT) && action == GLFW_RELEASE) {
		dPressed = false;
	}



	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
		spacePressed = true;
	}
	else if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE) {
		spacePressed = false;
	}

	if (key == GLFW_KEY_LEFT_CONTROL && action == GLFW_PRESS) {
		controlPressed = true;
	}
	else if (key == GLFW_KEY_LEFT_CONTROL && action == GLFW_RELEASE) {
		controlPressed = false;
	}

	if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_PRESS) {
		shiftPressed = true;
	}
	else if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_RELEASE) {
		shiftPressed = false;
	}





	if (key == GLFW_KEY_E && action == GLFW_PRESS) {
		camera.DisableMovementControls();
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
	else if (key == GLFW_KEY_E && action == GLFW_RELEASE) {
		camera.EnableMovementControls();
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}

	if (key == GLFW_KEY_T && action == GLFW_PRESS) {
		tPressed = true;
	}
	else if (key == GLFW_KEY_T && action == GLFW_RELEASE) {
		tPressed = false;
	}
}
static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{
	cursorXPos = (float)xpos;
	cursorYPos = (float)ypos;
}
static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		leftClicked = true;
	}
	else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		leftClicked = false;
	}

	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
		rightClicked = true;
	}
	else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE) {
		rightClicked = false;
	}
}
static void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	currentWidth = width;
	currentHeight = height;
	if (width > 0 && height > 0) {
		glViewport(0, 0, width, height);
	}
}

static GLuint loadSpriteSheet(const std::string texDir, const std::string texName, GLint textureWrapS, GLint textureWrapT, GLint textureMinFilter, GLint textureMaxFilter) {
	GLuint texID;
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);
	stbi_set_flip_vertically_on_load(1);

	int width, height, nrChannels;
	std::string str = texDir + texName;
	const char* c = str.c_str();
	unsigned char* data = stbi_load(c, &width, &height, &nrChannels, 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textureWrapS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textureWrapT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, textureMinFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, textureMaxFilter);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		printf("Failed to load texture!\n");
	}
	return texID;
}
static texCoords getImageCoordinates(unsigned int bottomLeftSquareX, unsigned int bottomLeftSquareY, unsigned int topRightSquareX, unsigned int topRightSquareY, unsigned int maxSquaresX, unsigned int maxSquaresY) {
	//4, 15, 6, 16
	texCoords answer;
	answer.bottomLeft = glm::vec2((float)bottomLeftSquareX / (float)maxSquaresX, (float)bottomLeftSquareY / (float)maxSquaresY);
	answer.topRight = glm::vec2((float)topRightSquareX / (float)maxSquaresX, (float)topRightSquareY / (float)maxSquaresY);
	return answer;
}



int main(void)
{
	GLFWwindow* window;

	if (!glfwInit()) {
		return -1;
	}

	if (fullscreen) {
		window = glfwCreateWindow(initialWidth, initialHeight, "Atlas", glfwGetPrimaryMonitor(), NULL);
	}
	else {
		window = glfwCreateWindow(initialWidth, initialHeight, "Atlas", NULL, NULL);
	}

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK) {
		printf("Error!\n");
	}

	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));

	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glfwSetKeyCallback(window, keyCallback);
		glfwSetCursorPosCallback(window, cursorPositionCallback);
		glfwSetMouseButtonCallback(window, mouseButtonCallback);
		glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBlendEquation(GL_ADD);
		glEnable(GL_DEPTH_TEST);


		GLuint frames[4] = { 
			loadSpriteSheet("res/images/", "f1.png", GL_REPEAT, GL_REPEAT, GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST),
			loadSpriteSheet("res/images/", "f2.png", GL_REPEAT, GL_REPEAT, GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST),
			loadSpriteSheet("res/images/", "f3.png", GL_REPEAT, GL_REPEAT, GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST),
			loadSpriteSheet("res/images/", "f4.png", GL_REPEAT, GL_REPEAT, GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST)
		};

		GLuint bckgrnd = loadSpriteSheet("res/images/", "background.png", GL_REPEAT, GL_REPEAT, GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST);
		GLuint sphereCow = loadSpriteSheet("res/images/", "newcow.png", GL_REPEAT, GL_REPEAT, GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST);
		GLuint letters = loadSpriteSheet("res/images/", "Letters.png", GL_REPEAT, GL_REPEAT, GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST);
		texCoords cursorCoords = getImageCoordinates(15, 15, 16, 16, 16, 16);

		CollidableSprite player = CollidableSprite(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(-0.5f, -0.5f), glm::vec2(0.5f, 0.5f), glm::vec2(-0.5f, -0.5f), glm::vec2(0.5f, 0.5f), 0.0f, glm::vec2(0.0f, 0.9375f), glm::vec2(0.0625f, 1.0f), frames[0], 0, 1.0f, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, glm::vec3(0.0f, -9.807f, 0.0f), 1.0f);
		Object background = Object(type::rectangle, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(-500.0f, -250.0f), glm::vec2(500.0f, 250.0), -1.0f, glm::vec2(0.0f, 0.0f), glm::vec2(100.0f, 100.0f), bckgrnd);
		Object aLetter = Object(type::rectangle, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(-0.5f, -1.0f), glm::vec2(0.5f, 1.0f), 1.0f, glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), letters);
		Object cursor = Object(type::rectangle, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(-0.5f, -0.5f), glm::vec2(0.5f, 0.5f), 1.0f, cursorCoords.bottomLeft, cursorCoords.topRight, frames[0]);
		
		std::vector<CollidableSprite> ground;
		for (unsigned int i = 0; i < 100; i++) {
			ground.push_back(CollidableSprite(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(i, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(-0.5f, -0.5f), glm::vec2(0.5f, 0.5f), 0.0f, glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), sphereCow, 0, 1.0f, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, glm::vec3(0.0f, 0.0f, 0.0f), 1.0f));
		}

		std::vector<CollidableSprite> food;
		texCoords meteor = getImageCoordinates(2, 13, 3, 14, 16, 16);
		srand(time(NULL));
		for (unsigned int i = 0; i < 200; i++) {
			float rx = (float)((rand() / (float)RAND_MAX * 100) - 50);
			float ry = (float)((rand() / (float)RAND_MAX * 50) - 25);
			float rsx = (float)((rand() / (float)RAND_MAX * 0.25) + 0.25);
			float rsy = (float)((rand() / (float)RAND_MAX * 0.25) + 0.25);
			int randInt = (int)std::round((rand() / (double)RAND_MAX * 4));
			glm::vec2 bottomLeftTexCoord;
			glm::vec2 topRightTexCoord;
			
			if (randInt == 0 || randInt == 4) {
				bottomLeftTexCoord = meteor.bottomLeft;
				topRightTexCoord = meteor.topRight;
			}
			else if (randInt == 1) {
				bottomLeftTexCoord = meteor.topRight;
				topRightTexCoord = meteor.bottomLeft;
			}
			else if (randInt == 2) {
				bottomLeftTexCoord = glm::vec2(meteor.topRight.x, meteor.bottomLeft.y);
				topRightTexCoord = glm::vec2(meteor.bottomLeft.x, meteor.topRight.y);
			}
			else if (randInt == 3) {
				bottomLeftTexCoord = glm::vec2(meteor.bottomLeft.x, meteor.topRight.y);
				topRightTexCoord = glm::vec2(meteor.topRight.x, meteor.bottomLeft.y);
			}
			food.push_back(CollidableSprite(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(rx, ry, 0.0f), glm::vec3(rsx, rsy, 1.0f), glm::vec2(-0.5f, -0.5f), glm::vec2(0.5f, 0.5f), 0.0f, bottomLeftTexCoord, topRightTexCoord, frames[0], 2, rsx*rsy, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, glm::vec3(0.0f, 0.0f, 0.0f), 1.0f));
		}

		texCoords ammoCoords = getImageCoordinates(0, 14, 2, 15, 16, 16);
		CollidableSprite ammo = CollidableSprite(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(-0.5f, -0.5f), glm::vec2(0.5f, 0.5f), 0.0f, ammoCoords.bottomLeft, ammoCoords.topRight, frames[0], 0, 1.0f, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, glm::vec3(0.0f, 0.0f, 0.0f), 1.0f);
		Simple2DRenderer renderer;

		glm::vec3 cameraTranslation(0.0f, 0.0f, 0.0f);
		glfwSetCursorPos(window, 0.0, 0.0);

		float timeConstant = 1.0f;
		
		Timer playerSpriteTimer = Timer(0.5f);
		playerSpriteTimer.Start();
		Timer meteorSpriteTimer = Timer(2.5f);
		meteorSpriteTimer.Start();
		Timer lungeTimer = Timer(2.5f);

		float scoreMultiplier = 1.0f;
		int score = 0.0f;
		double lastTime = glfwGetTime();
		double deltaT = 0, nowTime = 0;
		bool lungeReady = true;
		bool movementEnabled = true;
		bool clickingEnabled = true;
		bool zoomEnabled = true;
		bool gameOver = false;
		bool shot = false;
		bool midair = false;
		bool submitAmmoRender = false;
		bool flyEnabled = false;
		bool lungeEnabled = false;
		bool cursorEnabled = false;
		bool shootingEnabled = false;
		unsigned int actNumber = 0;
		movementSpeed = 0.01f;
		// mine is 0,1,2, mark is 3,4, and chris is 5

		ImGui::CreateContext();
		ImGui_ImplGlfwGL3_Init(window, false);
		ImGui::StyleColorsDark();
		
		while (!glfwWindowShouldClose(window))
		{
			nowTime = glfwGetTime();
			deltaT = (nowTime - lastTime);
			lastTime = nowTime;

			glClearColor(0.0f, 0.114f, 0.231f, 1.0f);
			glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
			ImGui_ImplGlfwGL3_NewFrame();

			float deltaTime = (float)deltaT * timeConstant;
			
			// Yanni first act
			if (actNumber == 0) {
				movementEnabled = true;
				flyEnabled = true;
				lungeEnabled = false;
				cursorEnabled = false;
				shootingEnabled = false;
				scoreMultiplier = 5.0f;
				player.SetGravitationalAcceleration(glm::vec3(0.0f, 0.0f, 0.0f));
				///////////////////////////////////////////////////////////////////////////
				if (movementEnabled) {
					if (zoomEnabled) {
						if (wPressed) {
							camera.MoveForward(deltaTime);
						}
						if (sPressed) {
							camera.MoveBackward(deltaTime);
						}
					}
					if (aPressed) {
						if (player.GetLinearVelocity().x > 0) {
							player.ApplyLinearVelocity(glm::vec3(-((movementSpeed/0.007777) * deltaTime), 0.0f, 0.0f));
						}
						else {
							camera.StrafeLeft(player, deltaTime);
						}
					}
					if (dPressed) {
						if (player.GetLinearVelocity().x > 0) {
							player.ApplyLinearVelocity(glm::vec3((movementSpeed/0.007777) * deltaTime, 0.0f, 0.0f));
						}
						else {
							camera.StrafeRight(player, deltaTime);
						}
					}
					if (spacePressed) {
						if (player.GetCanJump()) {
							if (!flyEnabled) {
								player.SetCanJump(false);
								player.ApplyLinearVelocity(glm::vec3(0.0f, (5.0f/0.007777) * deltaTime, 0.0f));
							}
							else {
								player.TranslateAdd3f(0.0f, movementSpeed/0.007777 * deltaTime, 0.0f);
							}
						}
					}
					if (flyEnabled) {
						if (controlPressed) {
							player.TranslateAdd3f(0.0f, -(movementSpeed/0.007777) * deltaTime, 0.0f);
						}
					}
					if (lungeEnabled) {
						if (lungeReady) {
							if (shiftPressed) {
								if (aPressed) {
									player.ApplyLinearVelocity(glm::vec3(-5.0f, 0.0f, 0.0f));
								}
								else if (dPressed) {
									player.ApplyLinearVelocity(glm::vec3(5.0f, 0.0f, 0.0f));
								}
								else {
									player.ApplyLinearVelocity(glm::vec3(0.0f, 5.0f, 0.0f));
								}
								lungeTimer.Start();
								lungeReady = false;
							}
						}
					}
				}
				if (shootingEnabled) {
					if (tPressed) {
						ammo.SetLinearVelocity(glm::vec3(0.0f, 0.0f, 0.0f));
						ammo.Rotate3f(0.0f, 0.0f, 0.0f);
						shot = false;
					}
				}
				if (clickingEnabled) {
					if (leftClicked) {
						if (shootingEnabled) {
							shot = true;
						}
					}
				}
				///////////////////////////////////////////////////////////////////////////
				camera.ChangeMovementSpeed(movementSpeed);
				camera.Follow(player);
				glm::vec3 camPos = camera.GetTranslation();
				///////////////////////////////////////////////////////////////////////////
				glm::mat4 viewMatrix = camera.GetViewTransformMatrix();
				glm::mat4 projectionMatrix;
				if (currentWidth > 0 && currentHeight > 0) {
					projectionMatrix = glm::perspective(glm::radians(FOV), (float)currentWidth / (float)currentHeight, 0.1f, 150.0f);
				}
				///////////////////////////////////////////////////////////////////////////
				renderer.submitForceRender(&background);
				///////////////////////////////////////////////////////////////////////////
				if (shootingEnabled) {
					if (shot) {
						if (!midair) {
							glm::vec3 playerPos = player.GetTranslation();
							glm::vec3 cursorPos = cursor.GetTranslation();
							glm::vec2 changeInValues = glm::vec2(cursorPos.x - playerPos.x, cursorPos.y - playerPos.y);
							float degrees = 0.0f;
							if (changeInValues.x == 0) {
								degrees = 90.0f;
							}
							else {
								degrees = glm::degrees(atan(changeInValues.y / changeInValues.x));
							}
							if ((degrees > -90.0f && degrees < 0.0f) && changeInValues.y > 0.0f) {
								degrees += 180.0f;
							}
							else if ((degrees < 90.0f && degrees > 0.0f) && changeInValues.y < 0.0f && changeInValues.x < 0.0f) {
								degrees += 180.0f;
							}
							ammo.Rotate3f(0.0f, 0.0f, degrees);
							glm::vec2 changeInValuesNormalized = glm::normalize(changeInValues);
							ammo.SetLinearVelocity(glm::vec3(changeInValuesNormalized.x * shootSpeed, changeInValuesNormalized.y * shootSpeed, 0.0f));
							midair = true;;
						}
						submitAmmoRender = true;
					}
					else {
						camera.BringWith(ammo);
						midair = false;
						submitAmmoRender = false;
					}
					ammo.Update(deltaTime);
				}
				///////////////////////////////////////////////////////////////////////////
				playerSpriteTimer.ElapseTime(deltaTime);
				if (playerSpriteTimer.HasFinished()) {
					player.Play(frames, 4);
					playerSpriteTimer.Reset(0.5f);
					playerSpriteTimer.Start();
				}
				///////////////////////////////////////////////////////////////////////////
				meteorSpriteTimer.ElapseTime(deltaTime);
				if (meteorSpriteTimer.HasFinished()) {
					for (unsigned int i = 0; i < food.size(); i++) {
						food[i].Play(frames, 4);
					}
					meteorSpriteTimer.Reset(2.5f);
					meteorSpriteTimer.Start();
				}
				///////////////////////////////////////////////////////////////////////////
				bool noneDisplayed = true;
				for (unsigned int i = 0; i < food.size(); i++) {
					if (food[i].IsDisplayed()) {
						IntersectData data = player.GetDoesIntersect(food[i]);
						if (data.GetDoesIntersect()) {
							glm::vec3 scale = food[i].GetScale();
							float value = std::sqrtf(scale.x * scale.x + scale.y * scale.y + scale.z + scale.z);
							int intValue = (int)((float)(value)*(scoreMultiplier));
							player.ScaleAdd3f(value / (scoreMultiplier * scoreMultiplier), value / (scoreMultiplier * scoreMultiplier), 0.0f);
							player.AddMass(food[i].GetMass());
							score += intValue;
							food[i].SetIsDisplayed(false);
						}
						else {
							glm::vec3 playerPos = player.GetTranslation();
							glm::vec3 foodPos = food[i].GetTranslation();
							glm::vec2 changeInValues = glm::vec2(playerPos.x - foodPos.x, playerPos.y - foodPos.y);
							float degrees = 0.0f;
							if (changeInValues.x == 0) {
								degrees = 90.0f;
							}
							else {
								degrees = glm::degrees(atan(changeInValues.y / changeInValues.x));
							}
							if ((degrees > -90.0f && degrees < 0.0f) && changeInValues.y > 0.0f) {
								degrees += 180.0f;
							}
							else if ((degrees < 90.0f && degrees > 0.0f) && changeInValues.y < 0.0f && changeInValues.x < 0.0f) {
								degrees += 180.0f;
							}
							glm::vec2 changeInValuesNormalized = glm::normalize(changeInValues);
							float meteorSpeed = 5 * player.GetMass() * food[i].GetMass() / (changeInValuesNormalized.x * changeInValuesNormalized.x + changeInValuesNormalized.y * changeInValuesNormalized.y);
							food[i].Stop();
							food[i].SetLinearAcceleration(glm::vec3(changeInValuesNormalized.x* meteorSpeed, changeInValuesNormalized.y* meteorSpeed, 0.0f));
							food[i].Update(deltaTime);
							renderer.submit(&food[i], camPos);
						}
						noneDisplayed = false;
					}
				}
				if (noneDisplayed) {
					actNumber = 1;
					player.Scale3f(1.0f, 1.0f, 1.0f);
					player.SetGravitationalAcceleration(glm::vec3(0.0f, -9.807f, 0.0f));
					player.Translate3f(0.0f, 1.0f, 0.0f);
					movementSpeed = 0.05f;
					/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					// SET ALL ACT 2 VALUES HERE
					/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				}
				///////////////////////////////////////////////////////////////////////////
				renderer.submit(&player, camPos);
				///////////////////////////////////////////////////////////////////////////

				renderer.flush(viewMatrix, projectionMatrix);
			} 
			
			// Mark first act
			if (actNumber == 3) {
				movementEnabled = true;
				flyEnabled = true;
				lungeEnabled = false;
				cursorEnabled = false;
				shootingEnabled = false;
				scoreMultiplier = 5.0f;
				player.SetGravitationalAcceleration(glm::vec3(0.0f, 0.0f, 0.0f));
				///////////////////////////////////////////////////////////////////////////
				if (movementEnabled) {
					if (zoomEnabled) {
						if (wPressed) {
							camera.MoveForward(deltaTime);
						}
						if (sPressed) {
							camera.MoveBackward(deltaTime);
						}
					}
					if (aPressed) {
						if (player.GetLinearVelocity().x > 0) {
							player.ApplyLinearVelocity(glm::vec3(-((movementSpeed / 0.007777) * deltaTime), 0.0f, 0.0f));
						}
						else {
							camera.StrafeLeft(player, deltaTime);
						}
					}
					if (dPressed) {
						if (player.GetLinearVelocity().x > 0) {
							player.ApplyLinearVelocity(glm::vec3((movementSpeed / 0.007777) * deltaTime, 0.0f, 0.0f));
						}
						else {
							camera.StrafeRight(player, deltaTime);
						}
					}
					if (spacePressed) {
						if (player.GetCanJump()) {
							if (!flyEnabled) {
								player.SetCanJump(false);
								player.ApplyLinearVelocity(glm::vec3(0.0f, (5.0f / 0.007777) * deltaTime, 0.0f));
							}
							else {
								player.TranslateAdd3f(0.0f, movementSpeed / 0.007777 * deltaTime, 0.0f);
							}
						}
					}
					if (flyEnabled) {
						if (controlPressed) {
							player.TranslateAdd3f(0.0f, -(movementSpeed / 0.007777) * deltaTime, 0.0f);
						}
					}
					if (lungeEnabled) {
						if (lungeReady) {
							if (shiftPressed) {
								if (aPressed) {
									player.ApplyLinearVelocity(glm::vec3(-5.0f, 0.0f, 0.0f));
								}
								else if (dPressed) {
									player.ApplyLinearVelocity(glm::vec3(5.0f, 0.0f, 0.0f));
								}
								else {
									player.ApplyLinearVelocity(glm::vec3(0.0f, 5.0f, 0.0f));
								}
								lungeTimer.Start();
								lungeReady = false;
							}
						}
					}
				}
				if (shootingEnabled) {
					if (tPressed) {
						ammo.SetLinearVelocity(glm::vec3(0.0f, 0.0f, 0.0f));
						ammo.Rotate3f(0.0f, 0.0f, 0.0f);
						shot = false;
					}
				}
				if (clickingEnabled) {
					if (leftClicked) {
						if (shootingEnabled) {
							shot = true;
						}
					}
				}
				///////////////////////////////////////////////////////////////////////////
				camera.ChangeMovementSpeed(movementSpeed);
				camera.Follow(player);
				glm::vec3 camPos = camera.GetTranslation();
				///////////////////////////////////////////////////////////////////////////
				glm::mat4 viewMatrix = camera.GetViewTransformMatrix();
				glm::mat4 projectionMatrix;
				if (currentWidth > 0 && currentHeight > 0) {
					projectionMatrix = glm::perspective(glm::radians(FOV), (float)currentWidth / (float)currentHeight, 0.1f, 150.0f);
				}
				///////////////////////////////////////////////////////////////////////////
				renderer.submitForceRender(&background);
				///////////////////////////////////////////////////////////////////////////
				if (shootingEnabled) {
					if (shot) {
						if (!midair) {
							glm::vec3 playerPos = player.GetTranslation();
							glm::vec3 cursorPos = cursor.GetTranslation();
							glm::vec2 changeInValues = glm::vec2(cursorPos.x - playerPos.x, cursorPos.y - playerPos.y);
							float degrees = 0.0f;
							if (changeInValues.x == 0) {
								degrees = 90.0f;
							}
							else {
								degrees = glm::degrees(atan(changeInValues.y / changeInValues.x));
							}
							if ((degrees > -90.0f && degrees < 0.0f) && changeInValues.y > 0.0f) {
								degrees += 180.0f;
							}
							else if ((degrees < 90.0f && degrees > 0.0f) && changeInValues.y < 0.0f && changeInValues.x < 0.0f) {
								degrees += 180.0f;
							}
							ammo.Rotate3f(0.0f, 0.0f, degrees);
							glm::vec2 changeInValuesNormalized = glm::normalize(changeInValues);
							ammo.SetLinearVelocity(glm::vec3(changeInValuesNormalized.x * shootSpeed, changeInValuesNormalized.y * shootSpeed, 0.0f));
							midair = true;;
						}
						submitAmmoRender = true;
					}
					else {
						camera.BringWith(ammo);
						midair = false;
						submitAmmoRender = false;
					}
					ammo.Update(deltaTime);
				}
				///////////////////////////////////////////////////////////////////////////
				playerSpriteTimer.ElapseTime(deltaTime);
				if (playerSpriteTimer.HasFinished()) {
					player.Play(frames, 4);
					playerSpriteTimer.Reset(0.5f);
					playerSpriteTimer.Start();
				}
				///////////////////////////////////////////////////////////////////////////
				meteorSpriteTimer.ElapseTime(deltaTime);
				if (meteorSpriteTimer.HasFinished()) {
					for (unsigned int i = 0; i < food.size(); i++) {
						food[i].Play(frames, 4);
					}
					meteorSpriteTimer.Reset(2.5f);
					meteorSpriteTimer.Start();
				}
				///////////////////////////////////////////////////////////////////////////
				bool noneDisplayed = true;
				for (unsigned int i = 0; i < food.size(); i++) {
					if (food[i].IsDisplayed()) {
						IntersectData data = player.GetDoesIntersect(food[i]);
						if (data.GetDoesIntersect()) {
							glm::vec3 scale = food[i].GetScale();
							float value = std::sqrtf(scale.x * scale.x + scale.y * scale.y + scale.z + scale.z);
							int intValue = (int)((float)(value) * (scoreMultiplier));
							player.ScaleAdd3f(value / (scoreMultiplier * scoreMultiplier), value / (scoreMultiplier * scoreMultiplier), 0.0f);
							player.AddMass(food[i].GetMass());
							score += intValue;
							food[i].SetIsDisplayed(false);
						}
						else {
							glm::vec3 playerPos = player.GetTranslation();
							glm::vec3 foodPos = food[i].GetTranslation();
							glm::vec2 changeInValues = glm::vec2(playerPos.x - foodPos.x, playerPos.y - foodPos.y);
							float degrees = 0.0f;
							if (changeInValues.x == 0) {
								degrees = 90.0f;
							}
							else {
								degrees = glm::degrees(atan(changeInValues.y / changeInValues.x));
							}
							if ((degrees > -90.0f && degrees < 0.0f) && changeInValues.y > 0.0f) {
								degrees += 180.0f;
							}
							else if ((degrees < 90.0f && degrees > 0.0f) && changeInValues.y < 0.0f && changeInValues.x < 0.0f) {
								degrees += 180.0f;
							}
							glm::vec2 changeInValuesNormalized = glm::normalize(changeInValues);
							float meteorSpeed = 5 * player.GetMass() * food[i].GetMass() / (changeInValuesNormalized.x * changeInValuesNormalized.x + changeInValuesNormalized.y * changeInValuesNormalized.y);
							food[i].Stop();
							food[i].SetLinearAcceleration(glm::vec3(changeInValuesNormalized.x * meteorSpeed, changeInValuesNormalized.y * meteorSpeed, 0.0f));
							food[i].Update(deltaTime);
							renderer.submit(&food[i], camPos);
						}
						noneDisplayed = false;
					}
				}
				if (noneDisplayed) {
					actNumber = 1;
					player.Scale3f(1.0f, 1.0f, 1.0f);
					player.SetGravitationalAcceleration(glm::vec3(0.0f, -9.807f, 0.0f));
					player.Translate3f(0.0f, 1.0f, 0.0f);
					movementSpeed = 0.05f;
					/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					// SET ALL ACT 2 VALUES HERE
					/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				}
				///////////////////////////////////////////////////////////////////////////
				renderer.submit(&player, camPos);
				///////////////////////////////////////////////////////////////////////////

				renderer.flush(viewMatrix, projectionMatrix);
			}

			{
				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			}

			ImGui::Render();
			ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}

	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
	return 0;
}