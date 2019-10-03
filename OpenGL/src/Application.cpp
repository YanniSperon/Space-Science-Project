#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <irrKlang.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>

#include "Shader.h"
#include "Mesh.h"
#include "Camera.h"
#include "Config.h"
#include "Object.h"
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
#include "Generator.h"
#include "Loader.h"
#include "Letters.h"
#include "ScoreDisplay.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/euler_angles.hpp"
#include "glm/gtx/quaternion.hpp"
#include "stb_image/stb_image.h"

//#include "imgui/imgui.h"
//#include "imgui/imgui_impl_glfw_gl3.h"

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

	irrklang::ISoundEngine* engine = irrklang::createIrrKlangDevice();

	if (!engine) {
		printf("Error creating irrKlang device\n");
	}

	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));

	{
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glfwSetKeyCallback(window, keyCallback);
		glfwSetCursorPosCallback(window, cursorPositionCallback);
		glfwSetMouseButtonCallback(window, mouseButtonCallback);
		glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBlendEquation(GL_ADD);
		glEnable(GL_DEPTH_TEST);
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		const char* attackSFXFilename = "res/audio/sfx/attack.wav";
		const char* explosionSFXFilename = "res/audio/sfx/explosion.wav";
		const char* jumpSFXFilename = "res/audio/sfx/jump.wav";
		const char* pickupSFXFilename = "res/audio/sfx/pickup.wav";
		const char* selectSFXFilename = "res/audio/sfx/select.wav";
		const char* shootSFXFilename = "res/audio/sfx/shoot.wav";
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		engine->setSoundVolume(0);
		irrklang::ISound* attackSFX = engine->play2D(attackSFXFilename, false, false, false, irrklang::ESM_AUTO_DETECT, false);
		irrklang::ISound* explosionSFX = engine->play2D(explosionSFXFilename, false, false, false, irrklang::ESM_AUTO_DETECT, false);
		irrklang::ISound* jumpSFX = engine->play2D(jumpSFXFilename, false, false, false, irrklang::ESM_AUTO_DETECT, false);
		irrklang::ISound* pickupSFX = engine->play2D(pickupSFXFilename, false, false, false, irrklang::ESM_AUTO_DETECT, false);
		irrklang::ISound* selectSFX = engine->play2D(selectSFXFilename, false, false, false, irrklang::ESM_AUTO_DETECT, false);
		irrklang::ISound* shootSFX = engine->play2D(shootSFXFilename, false, false, false, irrklang::ESM_AUTO_DETECT, false);
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		GLuint frames[4] = { 
			Loader::loadSpriteSheet("res/images/sprites/", "f1.png", GL_REPEAT, GL_REPEAT, GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST),
			Loader::loadSpriteSheet("res/images/sprites/", "f2.png", GL_REPEAT, GL_REPEAT, GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST),
			Loader::loadSpriteSheet("res/images/sprites/", "f3.png", GL_REPEAT, GL_REPEAT, GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST),
			Loader::loadSpriteSheet("res/images/sprites/", "f4.png", GL_REPEAT, GL_REPEAT, GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST)
		};
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		GLuint volcanoBackgroundFrame = Loader::loadSpriteSheet("res/images/backgrounds/volcano/", "volcanostill.png", GL_REPEAT, GL_REPEAT, GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST);
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		GLuint spaceBckgrnd = Loader::loadSpriteSheet("res/images/backgrounds/space/", "background.png", GL_REPEAT, GL_REPEAT, GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST);
		GLuint sphereCow = Loader::loadSpriteSheet("res/images/other/", "newcow.png", GL_REPEAT, GL_REPEAT, GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST);
		GLuint lettersTex = Loader::loadSpriteSheet("res/images/other/", "letters.png", GL_REPEAT, GL_REPEAT, GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST);
		GLuint lettersOutlined3PXTex = Loader::loadSpriteSheet("res/images/other/", "lettersoutlined3px.png", GL_REPEAT, GL_REPEAT, GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST);
		texCoords cursorCoords = Loader::getImageCoordinates(15, 15, 16, 16, 16, 16);
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		Object volcanoBackground = Object(type::rectangle, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(-10.0f, -5.0f), glm::vec2(10.0f, 5.0f), glm::vec2(-10.0f, -5.0f), glm::vec2(10.0f, 5.0f), -1.0f, glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), volcanoBackgroundFrame);
		CollidableSprite planet = CollidableSprite(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(-0.5f, -0.5f), glm::vec2(0.5f, 0.5f), glm::vec2(-0.5f, -0.5f), glm::vec2(0.5f, 0.5f), 0.0f, glm::vec2(0.0f, 0.9375f), glm::vec2(0.0625f, 1.0f), frames[0], 0, 1.0f, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, glm::vec3(0.0f, -9.807f, 0.0f), 1.0f);
		texCoords dinoCoords = Loader::getImageCoordinates(14, 0, 16, 1, 16, 16);
		CollidableSprite dino = CollidableSprite(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(-1.0f, -0.5f), glm::vec2(1.0f, 0.5f), glm::vec2(-1.0f, -0.5f), glm::vec2(1.0f, 0.5f), 0.0f, dinoCoords.bottomLeft, dinoCoords.topRight, frames[0], 0, 1.0f, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, glm::vec3(0.0f, -9.807f, 0.0f), 1.0f);
		Object background = Object(type::rectangle, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(-500.0f, -250.0f), glm::vec2(500.0f, 250.0), -1.0f, glm::vec2(0.0f, 0.0f), glm::vec2(100.0f, 100.0f), spaceBckgrnd);
		//Object aLetter = Object(type::rectangle, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(-0.5f, -1.0f), glm::vec2(0.5f, 1.0f), 1.0f, glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), letters);
		CollidableSprite cursor = CollidableSprite(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.002f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(-0.5f, -0.5f), glm::vec2(0.5f, 0.5f), 1.0f, cursorCoords.bottomLeft, cursorCoords.topRight, frames[0], 0, 1.0f, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, glm::vec3(0.0f, 0.0f, 0.0f), 1.0f);
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		std::vector<CollidableSprite> ground;
		for (unsigned int i = 0; i < 100; i++) {
			ground.push_back(CollidableSprite(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(i, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(-0.5f, -0.5f), glm::vec2(0.5f, 0.5f), 0.0f, glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), sphereCow, 0, 1.0f, glm::vec3(-5.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, glm::vec3(0.0f, 0.0f, 0.0f), 1.0f));
		}
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		std::vector<CollidableSprite> food;
		texCoords meteor = Loader::getImageCoordinates(2, 13, 3, 14, 16, 16);
		srand(time(NULL));
		for (unsigned int i = 0; i < 200; i++) {
			Generator::AddRandomMeteor(food, meteor, frames[0]);
		}
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		texCoords ammoCoords = Loader::getImageCoordinates(0, 14, 2, 15, 16, 16);
		CollidableSprite ammo = CollidableSprite(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(-0.5f, -0.5f), glm::vec2(0.5f, 0.5f), 0.001f, ammoCoords.bottomLeft, ammoCoords.topRight, frames[0], 0, 1.0f, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, glm::vec3(0.0f, 0.0f, 0.0f), 1.0f);
		Simple2DRenderer renderer;
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		texCoords satelliteCoords = Loader::getImageCoordinates(0, 11, 2, 13, 16, 16);
		CollidableSprite satellite = CollidableSprite(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 2.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(-0.5f, -0.5f), glm::vec2(0.5f, 0.5f), glm::vec2(-0.5f, -0.5f), glm::vec2(0.5f, 0.5f), 0.0f, satelliteCoords.bottomLeft, satelliteCoords.topRight, frames[0], 0, 1.0f, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, glm::vec3(0.0f, 0.0f, 0.0f), 1.0f);
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		std::vector<CollidableSprite> incomingMeteors;
		for (unsigned int i = 0; i < 10; i++) {
			Generator::AddRandomIncomingMeteor(incomingMeteors, meteor, frames[0], i);
		}/////////////////////////////////////////////////////////////////////////////////////////////////////
		std::vector<CollidableSprite> secondIncomingMeteors;
		for (unsigned int i = 0; i < 20; i++) {
			Generator::AddRandomIncomingMeteorFast(secondIncomingMeteors, meteor, frames[0], i);
		}
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		texCoords pool = Loader::getImageCoordinates(2, 15, 4, 16, 16, 16);
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		std::vector<CollidableSprite> pools;
		for (unsigned int i = 0; i < 10; i++) {
			Generator::AddPool(pools, pool, frames[0], i);
		}
		CollidableSprite p = CollidableSprite(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(-0.5f, -0.5f), glm::vec2(0.5f, 0.5f), glm::vec2(-0.5f, -0.5f), glm::vec2(0.5f, 0.5f), 0.0f, pool.bottomLeft, pool.topRight, frames[0], 0, 1.0f, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, glm::vec3(0.0f, -9.807f, 0.0f), 1.0f);
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		texCoords lavaTexCoords = Loader::getImageCoordinates(0, 9, 1, 10, 16, 16);
		CollidableSprite lavaOne = CollidableSprite(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(6.5f, 0.45, 0.0f), glm::vec3(1.75f, 1.75f, 1.75f), glm::vec2(-0.5f, -0.5f), glm::vec2(0.5f, 0.5f), glm::vec2(-0.5f, -0.5f), glm::vec2(0.5f, 0.5f), 0.0f, lavaTexCoords.bottomLeft, lavaTexCoords.topRight, frames[0], 0, 0.1f, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, glm::vec3(0.0f, -9.807f, 0.0f), 1.0f);
		CollidableSprite lavaTwo = CollidableSprite(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-6.5f, 0.45f, 0.0f), glm::vec3(1.75f, 1.75f, 1.75f), glm::vec2(-0.5f, -0.5f), glm::vec2(0.5f, 0.5f), glm::vec2(-0.5f, -0.5f), glm::vec2(0.5f, 0.5f), 0.0f, glm::vec2(lavaTexCoords.topRight.x, lavaTexCoords.bottomLeft.y), glm::vec2(lavaTexCoords.bottomLeft.x, lavaTexCoords.topRight.y), frames[0], 0, 0.1f, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, glm::vec3(0.0f, -9.807f, 0.0f), 1.0f);
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		texCoords volcanoTexCoords = Loader::getImageCoordinates(0, 0, 5, 3, 16, 16);
		Object volcanoOne = Object(type::rectangle, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-5.0f, -3.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(-5.0f, -2.5f), glm::vec2(5.0f, 2.5f), glm::vec2(-5.0f, -2.5f), glm::vec2(5.0f, 2.5f), -0.5f, volcanoTexCoords.bottomLeft, volcanoTexCoords.topRight, frames[0]);
		Object volcanoTwo = Object(type::rectangle, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(5.0f, -3.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(-5.0f, -2.5f), glm::vec2(5.0f, 2.5f), glm::vec2(-5.0f, -2.5f), glm::vec2(5.0f, 2.5f), -0.5f, glm::vec2(volcanoTexCoords.topRight.x, volcanoTexCoords.bottomLeft.y), glm::vec2(volcanoTexCoords.bottomLeft.x, volcanoTexCoords.topRight.y), frames[0]);
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		texCoords explosionTexCoords = Loader::getImageCoordinates(0, 10, 1, 11, 16, 16);
		Sprite explosion = Sprite(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(-0.5f, -0.5f), glm::vec2(0.5f, 0.5f), glm::vec2(-0.5f, -0.5f), glm::vec2(0.5f, 0.5f), 0.003f, explosionTexCoords.bottomLeft, explosionTexCoords.topRight, frames[0], 0);
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		texCoords steamTexCoords = Loader::getImageCoordinates(0, 8, 1, 9, 16, 16);
		Sprite steam = Sprite(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(-1.0f, -1.0f), glm::vec2(1.0f, 1.0f), glm::vec2(-1.0f, -1.0f), glm::vec2(1.0f, 1.0f), 0.003f, steamTexCoords.bottomLeft, steamTexCoords.topRight, frames[0], 0);
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		GLuint blackTex = 0;
		CollidableSprite startButton = CollidableSprite(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(3.0f, 1.0f, 1.0f), glm::vec2(-0.5f, -0.5f), glm::vec2(0.5f, 0.5f), glm::vec2(-0.5f, -0.5f), glm::vec2(0.5f, 0.5f), 0.0f, glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), blackTex, 0, 1.0f, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, glm::vec3(0.0f, 0.0f, 0.0f), 1.0f);
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		Letters startButtonText = Letters("Start", lettersTex, 1, glm::vec2(-1.2f, -0.4f), glm::vec2(1.2f, 0.4f), glm::vec3(0.25f, 0.5f, 0.0f));
		Letters titleScreenText = Letters("Welcome to game", lettersOutlined3PXTex, 1, glm::vec2(-4.2f, -0.4f), glm::vec2(4.2f, 0.4f), glm::vec3(0.25f, 2.0f, 0.0f));
		////////////////////////////////////////////////////////////////////
		texCoords aTex = Loader::getImageCoordinates(0, 15, 1, 16, 8, 16);
		////////////////////////////////////////////////////////////////////
		Letters scoreLabel = Letters("Score:", lettersOutlined3PXTex, 1, glm::vec2(-1.2f, -0.2f), glm::vec2(1.2f, 0.2f), glm::vec3(5.5f, 3.5f, 0.0f));
		ScoreDisplay scoreDisplay = ScoreDisplay(glm::vec2(-1.0f, -0.2f), glm::vec2(1.0f, 0.2f), 5, glm::vec3(8.0f, 3.5f, 0.0f), lettersOutlined3PXTex);
		////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////
		Object a = Object(type::rectangle, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(-0.5f, -0.5f), glm::vec2(0.5f, 0.5f), glm::vec2(-0.5f, -0.5f), glm::vec2(0.5f, 0.5f), 0.003f, aTex.bottomLeft, aTex.topRight, lettersTex);
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		glm::vec3 cameraTranslation(0.0f, 0.0f, 0.0f);
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		glfwSetCursorPos(window, 0.0, 0.0);
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		float timeConstant = 1.0f;
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		Timer planetSpriteTimer = Timer(0.5f);
		planetSpriteTimer.Start();
		Timer dinoSpriteTimer = Timer(0.5f);
		dinoSpriteTimer.Start();
		Timer meteorSpriteTimer = Timer(2.5f);
		meteorSpriteTimer.Start();
		Timer backgroundSpriteTimer = Timer(0.25f);
		backgroundSpriteTimer.Start();
		Timer volcanoOneSpriteTimer = Timer(0.4f);
		volcanoOneSpriteTimer.Start();
		Timer volcanoTwoSpriteTimer = Timer(0.6f);
		volcanoTwoSpriteTimer.Start();
		Timer explosionTimer = Timer(0.4f);
		explosionTimer.Start();
		Timer explosionSpriteTimer = Timer(0.1f);
		explosionSpriteTimer.Start();
		Timer steamTimer = Timer(0.4f);
		steamTimer.Start();
		Timer steamSpriteTimer = Timer(0.1f);
		steamSpriteTimer.Start();
		Timer lungeTimer = Timer(2.5f);
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		float scoreMultiplier = 1.0f;
		int score = 0;
		int lives = 3;
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
		bool exploding = false;
		bool steaming = false;
		int actNumber = -1;
		movementSpeed = 0.01f;
		movementEnabled = true;
		flyEnabled = true;
		lungeEnabled = false;
		cursorEnabled = false;
		shootingEnabled = false;
		scoreMultiplier = 5.0f;
		planet.SetGravitationalAcceleration(glm::vec3(0.0f, 0.0f, 0.0f));
		engine->setSoundVolume(1.0f);
		// mine is 0,1,2, mark is 3,4, and chris is 5
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		/*ImGui::CreateContext();
		ImGui_ImplGlfwGL3_Init(window, false);
		ImGui::StyleColorsDark();*/
		
		while (!glfwWindowShouldClose(window))
		{
			nowTime = glfwGetTime();
			deltaT = (nowTime - lastTime);
			lastTime = nowTime;

			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
			/*ImGui_ImplGlfwGL3_NewFrame();*/

			float deltaTime = (float)deltaT * timeConstant;
			
			// Title screen
			if (actNumber == -1) {
				glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
				glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
				if (leftClicked) {
					if (startButton.IsPointInside(cursor.GetTranslation()).GetDoesIntersect()) {
						actNumber = 0;
						score = 0;
						lives = 3;
						lungeReady = true;
						movementEnabled = true;
						clickingEnabled = true;
						zoomEnabled = true;
						gameOver = false;
						shot = false;
						midair = false;
						submitAmmoRender = false;
						flyEnabled = false;
						lungeEnabled = false;
						cursorEnabled = false;
						shootingEnabled = false;
						exploding = false;
						steaming = false;
						movementSpeed = 0.01f;
						movementEnabled = true;
						flyEnabled = true;
						lungeEnabled = false;
						cursorEnabled = false;
						shootingEnabled = false;
						scoreMultiplier = 5.0f;
					}
				}
				camera.Translate3f(0.0f, 0.0f, 5.0f);
				glm::vec3 camPos = camera.GetTranslation();
				///////////////////////////////////////////////////////////////////////////
				glm::mat4 viewMatrix = camera.GetViewTransformMatrix();
				glm::mat4 projectionMatrix;
				if (currentWidth > 0 && currentHeight > 0) {
					projectionMatrix = glm::perspective(glm::radians(FOV), (float)currentWidth / (float)currentHeight, 0.1f, 150.0f);
				}				
				///////////////////////////////////////////////////////////////////////////
				renderer.submitForceRender(&startButton);
				///////////////////////////////////////////////////////////////////////////
		
				//sentence1.SubmitForceRender(renderer);
				//renderer.submitForceRender(&a);
				startButtonText.SubmitForceRender(renderer);
				titleScreenText.SubmitForceRender(renderer);
				//renderer.submitForceRender(&a);
				////////////////////////////////////////////////////////////////////////////
				cursor.Translate3f(cursorXPos * mouseSensitivity, -cursorYPos * mouseSensitivity, 0.002f);
				renderer.submitForceRender(&cursor);
				///////////////////////////////////////////////////////////////////////////
				renderer.flush(viewMatrix, projectionMatrix);
				///////////////////////////////////////////////////////////////////////////
				//FIND ME 0
				if (!false) {
					actNumber = 0;
					score = 0;
					lives = 3;
					lungeReady = true;
					movementEnabled = true;
					clickingEnabled = true;
					zoomEnabled = true;
					gameOver = false;
					shot = false;
					midair = false;
					submitAmmoRender = false;
					flyEnabled = false;
					lungeEnabled = false;
					cursorEnabled = false;
					shootingEnabled = false;
					exploding = false;
					steaming = false;
					movementSpeed = 0.01f;
					movementEnabled = true;
					flyEnabled = true;
					lungeEnabled = false;
					cursorEnabled = false;
					shootingEnabled = false;
					scoreMultiplier = 5.0f;
				}
			}



			// Yanni first act
			if (actNumber == 0) {
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
						if (planet.GetLinearVelocity().x > 0) {
							planet.ApplyLinearVelocity(glm::vec3(-((movementSpeed/0.007777) * deltaTime), 0.0f, 0.0f));
						}
						else {
							camera.StrafeLeft(planet, deltaTime);
						}
					}
					if (dPressed) {
						if (planet.GetLinearVelocity().x > 0) {
							planet.ApplyLinearVelocity(glm::vec3((movementSpeed/0.007777) * deltaTime, 0.0f, 0.0f));
						}
						else {
							camera.StrafeRight(planet, deltaTime);
						}
					}
					if (spacePressed) {
						if (planet.GetCanJump()) {
							if (!flyEnabled) {
								planet.SetCanJump(false);
								planet.ApplyLinearVelocity(glm::vec3(0.0f, (5.0f/0.007777) * deltaTime, 0.0f));
							}
							else {
								planet.TranslateAdd3f(0.0f, movementSpeed/0.007777 * deltaTime, 0.0f);
							}
						}
					}
					if (flyEnabled) {
						if (controlPressed) {
							planet.TranslateAdd3f(0.0f, -(movementSpeed/0.007777) * deltaTime, 0.0f);
						}
					}
				}
				///////////////////////////////////////////////////////////////////////////
				camera.ChangeMovementSpeed(movementSpeed);
				camera.Follow(planet);
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
				planetSpriteTimer.ElapseTime(deltaTime);
				if (planetSpriteTimer.HasFinished()) {
					planet.Play(frames, 4);
					planetSpriteTimer.Reset(0.5f);
					planetSpriteTimer.Start();
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
				bool anyDisplayed = false;
				for (unsigned int i = 0; i < food.size(); i++) {
					if (food[i].IsDisplayed()) {
						IntersectData data = planet.GetDoesIntersect(food[i]);
						if (data.GetDoesIntersect()) {
							glm::vec3 scale = food[i].GetScale();
							float value = std::sqrtf(scale.x * scale.x + scale.y * scale.y + scale.z + scale.z);
							int intValue = (int)((float)(value)*(scoreMultiplier));
							planet.ScaleAdd3f(value / ((scoreMultiplier * scoreMultiplier) * 2), value / ((scoreMultiplier * scoreMultiplier) * 2), 0.0f);
							planet.AddMass(food[i].GetMass());
							score += intValue;
							food[i].SetIsDisplayed(false);
						}
						else {
							glm::vec3 planetPos = planet.GetTranslation();
							glm::vec3 foodPos = food[i].GetTranslation();
							glm::vec2 changeInValues = glm::vec2(planetPos.x - foodPos.x, planetPos.y - foodPos.y);
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
							float meteorSpeed = 5 * planet.GetMass() * food[i].GetMass() / (changeInValuesNormalized.x * changeInValuesNormalized.x + changeInValuesNormalized.y * changeInValuesNormalized.y);
							food[i].Stop();
							food[i].SetLinearAcceleration(glm::vec3(changeInValuesNormalized.x* meteorSpeed, changeInValuesNormalized.y* meteorSpeed, 0.0f));
							food[i].Update(deltaTime);
							renderer.submit(&food[i], camPos);
						}
						anyDisplayed = true;
					}
				}
				///////////////////////////////////////////////////////////////////////////
				// FIND ME 1
				if (!!anyDisplayed) {
					actNumber = 1;
					movementSpeed = 0.05f;
					shootSpeed = 15.0f;
					glfwSetCursorPos(window, 0.0, 0.0);
					movementEnabled = true;
					flyEnabled = false;
					lungeEnabled = false;
					cursorEnabled = false;
					shootingEnabled = false;
					scoreMultiplier = 5.0f;
					planet.Scale3f(1.0f, 1.0f, 1.0f);
					planet.Translate3f(0.0f, 0.0f, 0.0f);
					camera.Translate3f(0.0f, 1.0f, 5.0f);
				}
				///////////////////////////////////////////////////////////////////////////
				renderer.submit(&planet, camPos);
				///////////////////////////////////////////////////////////////////////////
				scoreLabel.TranslateVec3(glm::vec3(camPos.x, camPos.y, 0.0f));
				scoreLabel.SubmitForceRender(renderer);
				scoreDisplay.TranslateVec3(glm::vec3(camPos.x, camPos.y, 0.0f));
				scoreDisplay.DisplayScore(score, renderer);
				///////////////////////////////////////////////////////////////////////////

				renderer.flush(viewMatrix, projectionMatrix);
			} 
			// Yanni second act
			if (actNumber == 1) {
				///////////////////////////////////////////////////////////////////////////
				if (movementEnabled) {
					if (dPressed) {
						for (unsigned int i = 0; i < pools.size(); i++) {
							glm::vec3 poolsTrans = pools[i].GetTranslation();
							if (poolsTrans.y < 10.0f && pools[i].IsDisplayed() && poolsTrans.x < 7.5f) {
								pools[i].TranslateAdd3f((movementSpeed / 0.007777)* deltaTime, 0.0f, 0.0f);
							}
						}
					}
					if (aPressed) {
						for (unsigned int i = 0; i < pools.size(); i++) {
							glm::vec3 poolsTrans = pools[i].GetTranslation();
							if (poolsTrans.y < 10.0f && pools[i].IsDisplayed() && poolsTrans.x > -7.5f) {
								pools[i].TranslateAdd3f((-movementSpeed / 0.007777) * deltaTime, 0.0f, 0.0f);
							}
						}
					}
				}
				///////////////////////////////////////////////////////////////////////////
				glm::vec3 camPos = camera.GetTranslation();
				///////////////////////////////////////////////////////////////////////////
				glm::mat4 viewMatrix = camera.GetViewTransformMatrix();
				glm::mat4 projectionMatrix;
				if (currentWidth > 0 && currentHeight > 0) {
					projectionMatrix = glm::perspective(glm::radians(FOV), (float)currentWidth / (float)currentHeight, 0.1f, 150.0f);
				}
				///////////////////////////////////////////////////////////////////////////
				renderer.submitForceRender(&volcanoBackground);
				///////////////////////////////////////////////////////////////////////////
				renderer.submit(&volcanoOne, camPos);
				renderer.submit(&volcanoTwo, camPos);
				///////////////////////////////////////////////////////////////////////////
				bool anyDisplayed = false;
				for (unsigned int i = 0; i < pools.size(); i++) {
					if (pools[i].IsDisplayed()) {
						if (pools[i].GetDoesIntersect(lavaOne).GetDoesIntersect()) {
							pools[i].SetIsDisplayed(false);
							steaming = true;
							glm::vec3 changeInValues = pools[i].GetTranslation() - lavaOne.GetTranslation();
							glm::vec3 value = pools[i].GetTranslation() - changeInValues / 2.0f;
							steam.TranslateVec3(value);
							steamTimer.Reset(0.4f);
							steamTimer.Start();
							steamSpriteTimer.Reset(0.1f);
							steamSpriteTimer.Start();
							score += 100;
						}
						else if (pools[i].GetDoesIntersect(lavaTwo).GetDoesIntersect()) {
							pools[i].SetIsDisplayed(false);
							steaming = true;
							glm::vec3 changeInValues = pools[i].GetTranslation() - lavaTwo.GetTranslation();
							glm::vec3 value = pools[i].GetTranslation() - changeInValues / 2.0f;
							steam.TranslateVec3(value);
							steamTimer.Reset(0.4f);
							steamTimer.Start();
							steamSpriteTimer.Reset(0.1f);
							steamSpriteTimer.Start();
							score += 100;
						}
						if (pools[i].GetTranslation().y < -10) {
							pools[i].SetIsDisplayed(false);
						}
						pools[i].Update(deltaTime);
						renderer.submit(&pools[i], camPos);
						anyDisplayed = true;
					}
				}
				///////////////////////////////////////////////////////////////////////////
				// FIND ME 2
				if (!!anyDisplayed) {
					actNumber = 2;
					cursorEnabled = true;
					shootingEnabled = true;
					movementEnabled = false;
					meteorSpriteTimer.Reset(0.5f);
					meteorSpriteTimer.Start();
				}
				///////////////////////////////////////////////////////////////////////////
				volcanoOneSpriteTimer.ElapseTime(deltaTime);
				if (volcanoOneSpriteTimer.HasFinished()) {
					lavaOne.PlayReversible(frames, 4);
					volcanoOneSpriteTimer.Reset(0.4f);
					volcanoOneSpriteTimer.Start();
				}
				///////////////////////////////////////////////////////////////////////////
				volcanoTwoSpriteTimer.ElapseTime(deltaTime);
				if (volcanoTwoSpriteTimer.HasFinished()) {
					lavaTwo.PlayReversible(frames, 4);
					volcanoTwoSpriteTimer.Reset(0.6f);
					volcanoTwoSpriteTimer.Start();
				}
				///////////////////////////////////////////////////////////////////////////
				renderer.submit(&lavaOne, camPos);
				renderer.submit(&lavaTwo, camPos);
				///////////////////////////////////////////////////////////////////////////

				if (steaming) {
					renderer.submit(&steam, camPos);
					steamTimer.ElapseTime(deltaTime);
					steamSpriteTimer.ElapseTime(deltaTime);
					if (steamSpriteTimer.HasFinished()) {
						steam.Play(frames, 4);
						steamSpriteTimer.Reset(0.1f);
						steamSpriteTimer.Start();
					}
					if (steamTimer.HasFinished()) {
						steaming = false;
						steamTimer.Reset(0.4f);
						steamTimer.Start();
					}
				}

				///////////////////////////////////////////////////////////////////////////
				scoreLabel.TranslateVec3(glm::vec3(camPos.x, camPos.y, 0.0f));
				scoreLabel.SubmitForceRender(renderer);
				scoreDisplay.TranslateVec3(glm::vec3(camPos.x, camPos.y, 0.0f));
				scoreDisplay.DisplayScore(score, renderer);
				///////////////////////////////////////////////////////////////////////////

				renderer.flush(viewMatrix, projectionMatrix);
			}



			// Mark first act
			if (actNumber == 2) {
				///////////////////////////////////////////////////////////////////////////
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
							if (!midair) {
								shot = true;
								engine->play2D(shootSFXFilename, false, false, false, irrklang::ESM_AUTO_DETECT, false);
							}
						}
					}
				}
				///////////////////////////////////////////////////////////////////////////
				camera.ChangeMovementSpeed(movementSpeed);
				camera.Translate3f(0.0f, 0.0f, 5.0f);
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
							glm::vec3 satellitePos = satellite.GetTranslation();
							glm::vec3 cursorPos = cursor.GetTranslation();
							glm::vec2 changeInValues = glm::vec2(cursorPos.x - satellitePos.x, cursorPos.y - satellitePos.y);
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
						satellite.BringWith(ammo);
						midair = false;
						submitAmmoRender = false;
					}
					ammo.Update(deltaTime);
					if (ammo.GetTranslation().x < -10.0f || ammo.GetTranslation().x > 10.0f || ammo.GetTranslation().y < -10.0f || ammo.GetTranslation().y > 10.0f) {
						ammo.SetLinearVelocity(glm::vec3(0.0f, 0.0f, 0.0f));
						shot = false;
					}
				}
				///////////////////////////////////////////////////////////////////////////
				if (planet.GetDoesIntersect(ammo).GetDoesIntersect()) {
					engine->play2D(explosionSFXFilename, false, false, false, irrklang::ESM_AUTO_DETECT, false);
					ammo.SetLinearVelocity(glm::vec3(0.0f, 0.0f, 0.0f));
					shot = false;
					exploding = true;
					explosion.TranslateVec3(ammo.GetTranslation());
					explosionTimer.Reset(0.4f);
					explosionTimer.Start();
					explosionSpriteTimer.Reset(0.1f);
					explosionSpriteTimer.Start();
					lives--;
				}
				///////////////////////////////////////////////////////////////////////////
				renderer.submit(&satellite, camPos);
				///////////////////////////////////////////////////////////////////////////
				planet.Translate3f(-4.0f, 0.0f, 0.0f);
				planet.Scale3f(7.5f, 7.5f, 7.5f);
				planetSpriteTimer.ElapseTime(deltaTime);
				if (planetSpriteTimer.HasFinished()) {
					planet.Play(frames, 4);
					planetSpriteTimer.Reset(0.5f);
					planetSpriteTimer.Start();
				}
				renderer.submit(&planet, camPos);
				///////////////////////////////////////////////////////////////////////////
				if (submitAmmoRender) {
					renderer.submitForceRender(&ammo);
				}
				///////////////////////////////////////////////////////////////////////////
				bool anyDisplayed = false;
				for (unsigned int i = 0; i < incomingMeteors.size(); i++) {
					if (incomingMeteors[i].IsDisplayed()) {
						if (incomingMeteors[i].GetDoesIntersect(planet).GetDoesIntersect()) {
							incomingMeteors[i].SetIsDisplayed(false);
							engine->play2D(explosionSFXFilename, false, false, false, irrklang::ESM_AUTO_DETECT, false);
							exploding = true;
							explosion.TranslateVec3(incomingMeteors[i].GetTranslation());
							explosionTimer.Reset(0.4f);
							explosionTimer.Start();
							explosionSpriteTimer.Reset(0.1f);
							explosionSpriteTimer.Start();
							lives--;
						}
						else if (!(incomingMeteors[i].GetTranslation().x > -25.0f)) {
							incomingMeteors[i].SetIsDisplayed(false);
						}
						if (ammo.GetDoesIntersect(incomingMeteors[i]).GetDoesIntersect()) {
							incomingMeteors[i].SetIsDisplayed(false);
							engine->play2D(explosionSFXFilename, false, false, false, irrklang::ESM_AUTO_DETECT, false);
							ammo.SetLinearVelocity(glm::vec3(0.0f, 0.0f, 0.0f));
							exploding = true;
							glm::vec3 meteorPos = incomingMeteors[i].GetTranslation();
							glm::vec3 ammoPos = ammo.GetTranslation();
							glm::vec3 changeInValues = meteorPos - ammoPos;
							glm::vec3 dividedValue = changeInValues / 2.0f;
							glm::vec3 explosionPos = ammoPos + dividedValue;
							explosion.TranslateVec3(explosionPos);
							explosionTimer.Reset(0.4f);
							explosionTimer.Start();
							explosionSpriteTimer.Reset(0.1f);
							explosionSpriteTimer.Start();
							shot = false;
							score += 100;
						}
						if (satellite.GetDoesIntersect(incomingMeteors[i]).GetDoesIntersect()) {
							incomingMeteors[i].SetIsDisplayed(false);
							engine->play2D(explosionSFXFilename, false, false, false, irrklang::ESM_AUTO_DETECT, false);
							exploding = true;
							glm::vec3 meteorPos = incomingMeteors[i].GetTranslation();
							glm::vec3 satellitePos = satellite.GetTranslation();
							glm::vec3 changeInValues = meteorPos - satellitePos;
							glm::vec3 dividedValue = changeInValues / 2.0f;
							glm::vec3 explosionPos = satellitePos + dividedValue;
							explosion.TranslateVec3(explosionPos);
							explosionTimer.Reset(0.4f);
							explosionTimer.Start();
							explosionSpriteTimer.Reset(0.1f);
							explosionSpriteTimer.Start();
						}
						incomingMeteors[i].Update(deltaTime);
						renderer.submit(&incomingMeteors[i], camPos);
						anyDisplayed = true;
					}
				}
				// FIND ME 3
				if (!!anyDisplayed || lives == 0) {
					actNumber = 3;
					lives = 3;
				}
				meteorSpriteTimer.ElapseTime(deltaTime);
				if (meteorSpriteTimer.HasFinished()) {
					for (unsigned int i = 0; i < incomingMeteors.size(); i++) {
						if (incomingMeteors[i].IsDisplayed()) {
							incomingMeteors[i].Play(frames, 4);
						}
					}
					meteorSpriteTimer.Reset(0.5f);
					meteorSpriteTimer.Start();
				}
				if (exploding) {
					renderer.submit(&explosion, camPos);
					explosionTimer.ElapseTime(deltaTime);
					explosionSpriteTimer.ElapseTime(deltaTime);
					if (explosionSpriteTimer.HasFinished()) {
						explosion.Play(frames, 4);
						explosionSpriteTimer.Reset(0.1f);
						explosionSpriteTimer.Start();
					}
					if (explosionTimer.HasFinished()) {
						exploding = false;
						explosionTimer.Reset(0.4f);
						explosionTimer.Start();
					}
				}
				///////////////////////////////////////////////////////////////////////////
				if (cursorEnabled) {
					cursor.Translate3f(cursorXPos * mouseSensitivity, -cursorYPos * mouseSensitivity, 0.002f);
					renderer.submitForceRender(&cursor);
				}
				///////////////////////////////////////////////////////////////////////////
				scoreLabel.TranslateVec3(glm::vec3(camPos.x, camPos.y, 0.0f));
				scoreLabel.SubmitForceRender(renderer);
				scoreDisplay.TranslateVec3(glm::vec3(camPos.x, camPos.y, 0.0f));
				scoreDisplay.DisplayScore(score, renderer);
				///////////////////////////////////////////////////////////////////////////
				renderer.flush(viewMatrix, projectionMatrix);
				///////////////////////////////////////////////////////////////////////////
			}
			// Mark second act
			if (actNumber == 3) {
				///////////////////////////////////////////////////////////////////////////
				camera.ChangeMovementSpeed(movementSpeed);
				camera.Translate3f(0.0f, 0.0f, 5.0f);
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
				planet.Translate3f(-4.0f, 0.0f, 0.0f);
				planet.Scale3f(7.5f, 7.5f, 7.5f);
				planetSpriteTimer.ElapseTime(deltaTime);
				if (planetSpriteTimer.HasFinished()) {
					planet.Play(frames, 4);
					planetSpriteTimer.Reset(0.5f);
					planetSpriteTimer.Start();
				}
				renderer.submit(&planet, camPos);
				///////////////////////////////////////////////////////////////////////////
				bool anyDisplayed = false;
				for (unsigned int i = 0; i < secondIncomingMeteors.size(); i++) {
					if (secondIncomingMeteors[i].IsDisplayed()) {
						if (secondIncomingMeteors[i].GetDoesIntersect(planet).GetDoesIntersect()) {
							secondIncomingMeteors[i].SetIsDisplayed(false);
							engine->play2D(explosionSFXFilename, false, false, false, irrklang::ESM_AUTO_DETECT, false);
							exploding = true;
							explosion.TranslateVec3(secondIncomingMeteors[i].GetTranslation());
							explosionTimer.Reset(0.4f);
							explosionTimer.Start();
							explosionSpriteTimer.Reset(0.1f);
							explosionSpriteTimer.Start();
							lives--;
						}
						else if (!(secondIncomingMeteors[i].GetTranslation().x > -25.0f)) {
							secondIncomingMeteors[i].SetIsDisplayed(false);
						}
						secondIncomingMeteors[i].Update(deltaTime);
						renderer.submit(&secondIncomingMeteors[i], camPos);
						anyDisplayed = true;
					}
				}
				// FIND ME 4
				if (!!anyDisplayed || lives == -17) {
					actNumber = 4;
					movementEnabled = true;
				}
				meteorSpriteTimer.ElapseTime(deltaTime);
				if (meteorSpriteTimer.HasFinished()) {
					for (unsigned int i = 0; i < secondIncomingMeteors.size(); i++) {
						if (secondIncomingMeteors[i].IsDisplayed()) {
							secondIncomingMeteors[i].Play(frames, 4);
						}
					}
					meteorSpriteTimer.Reset(0.5f);
					meteorSpriteTimer.Start();
				}
				if (exploding) {
					renderer.submit(&explosion, camPos);
					explosionTimer.ElapseTime(deltaTime);
					explosionSpriteTimer.ElapseTime(deltaTime);
					if (explosionSpriteTimer.HasFinished()) {
						explosion.Play(frames, 4);
						explosionSpriteTimer.Reset(0.1f);
						explosionSpriteTimer.Start();
					}
					if (explosionTimer.HasFinished()) {
						exploding = false;
						explosionTimer.Reset(0.4f);
						explosionTimer.Start();
					}
				}
				///////////////////////////////////////////////////////////////////////////
				scoreLabel.TranslateVec3(glm::vec3(camPos.x, camPos.y, 0.0f));
				scoreLabel.SubmitForceRender(renderer);
				scoreDisplay.TranslateVec3(glm::vec3(camPos.x, camPos.y, 0.0f));
				scoreDisplay.DisplayScore(score, renderer);
				///////////////////////////////////////////////////////////////////////////
				renderer.flush(viewMatrix, projectionMatrix);
				///////////////////////////////////////////////////////////////////////////
			}



			// Chris first act
			if (actNumber == 4) {
				///////////////////////////////////////////////////////////////////////////
				if (zoomEnabled) {
					if (wPressed) {
						camera.MoveForward(deltaTime);
					}
					if (sPressed) {
						camera.MoveBackward(deltaTime);
					}
				}
				if (aPressed) {
					if (dino.GetLinearVelocity().x > 0.0f) {
						dino.ApplyLinearVelocity(glm::vec3(-((movementSpeed / 0.007777) * deltaTime), 0.0f, 0.0f));
					}
					else {
						dino.StrafeLeft(deltaTime, movementSpeed);
					}
				}
				if (dPressed) {
					if (dino.GetLinearVelocity().x < 0.0f) {
						dino.ApplyLinearVelocity(glm::vec3((movementSpeed / 0.007777) * deltaTime, 0.0f, 0.0f));
					}
					else {
						dino.StrafeRight(deltaTime, movementSpeed);
					}
				}
				if (spacePressed) {
					if (dino.GetCanJump()) {
						dino.SetCanJump(false);
						dino.ApplyLinearVelocity(glm::vec3(0.0f, (5.0f / 0.007777) * deltaTime, 0.0f));
					}
				}
				///////////////////////////////////////////////////////////////////////////
				camera.Follow(dino);
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
				dinoSpriteTimer.ElapseTime(deltaTime);
				if (dinoSpriteTimer.HasFinished()) {
					dino.Play(frames, 4);
					dinoSpriteTimer.Reset(0.5f);
					dinoSpriteTimer.Start();
				}
				///////////////////////////////////////////////////////////////////////////
				dino.UpdateCollision(deltaTime, ground);
				/*dino.Update(deltaTime);
				if (dino.GetTranslation().y < 1.0f) {
					glm::vec3 previousVel = dino.GetLinearVelocity();
					glm::vec3 previousPos = dino.GetTranslation();
					dino.SetLinearVelocity(glm::vec3(previousVel.x, 0.0f, previousVel.z));
					dino.SetCanJump(true);
					dino.TranslateVec3(glm::vec3(previousPos.x, 1.0f, 0.0f));
				}
				else {
				}*/
				bool anyDisplayed = false;
				for (unsigned int i = 0; i < ground.size(); i++) {
					renderer.submit(&ground[i], camPos);
					anyDisplayed = true;
				}
				///////////////////////////////////////////////////////////////////////////
				// FIND ME 5
				if (!anyDisplayed) {
					actNumber = 1;
					movementSpeed = 0.05f;
					shootSpeed = 15.0f;
					glfwSetCursorPos(window, 0.0, 0.0);
					movementEnabled = true;
					flyEnabled = false;
					lungeEnabled = false;
					cursorEnabled = false;
					shootingEnabled = false;
					scoreMultiplier = 5.0f;
					dino.Scale3f(1.0f, 1.0f, 1.0f);
					dino.Translate3f(0.0f, 0.0f, 0.0f);
					camera.Translate3f(0.0f, 1.0f, 5.0f);
				}
				///////////////////////////////////////////////////////////////////////////
				renderer.submit(&dino, camPos);
				///////////////////////////////////////////////////////////////////////////
				scoreLabel.TranslateVec3(glm::vec3(camPos.x, camPos.y, 0.0f));
				scoreLabel.SubmitForceRender(renderer);
				scoreDisplay.TranslateVec3(glm::vec3(camPos.x, camPos.y, 0.0f));
				scoreDisplay.DisplayScore(score, renderer);
				///////////////////////////////////////////////////////////////////////////

				renderer.flush(viewMatrix, projectionMatrix);
			}
			/*{
				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			}*/

			/*ImGui::Render();
			ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());*/
			glfwSwapBuffers(window);
			glfwPollEvents();
		}

		if (shootSFX) {
			shootSFX->drop();
		}
		if (attackSFX) {
			attackSFX->drop();
		}
		if (explosionSFX) {
			explosionSFX->drop();
		}
		if (jumpSFX) {
			jumpSFX->drop();
		}
		if (pickupSFX) {
			pickupSFX->drop();
		}
		if (selectSFX) {
			selectSFX->drop();
		}

		engine->drop();
	}

	/*ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();*/
	glfwTerminate();
	return 0;
}