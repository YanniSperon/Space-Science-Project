#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>

#include "Shader.h"
#include "Mesh.h"
#include "Camera.h"
#include "Config.h"
#include "Object.h"
#include "Player.h"
#include "PhysicsBody.h"
#include "BoundingSphere.h"
#include "IntersectData.h"
#include "Plane.h"
#include "Sprite.h"
#include "SpritePhysicsBody.h"
#include "Timer.h"
#include "CollidableSprite.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/euler_angles.hpp"
#include "glm/gtx/quaternion.hpp"
#include "primitives/Vertex.h"
#include "primitives/ShapeGenerator.h"
#include "stb_image/stb_image.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"

// https://www.youtube.com/watch?v=fUO9tk6IarY&list=PLEETnX-uPtBXm1KEr_2zQ6K_0hoGH6JJ0&index=7 - 00:31

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

static int oldMouseX = 0;
static int oldMouseY = 0;
static float movementSpeed = 0.05f;

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
//static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
//{
//	if (ypos * mouseSensitivity > 1.5708) {
//		double newMouseY = 1.57 / mouseSensitivity;
//		glfwSetCursorPos(window, xpos, newMouseY);
//		camera.LookAt(xpos, newMouseY);
//	}
//	else if (ypos * mouseSensitivity < -1.5708) {
//		double newMouseY = -1.57 / mouseSensitivity;
//		glfwSetCursorPos(window, xpos, newMouseY);
//		camera.LookAt(xpos, newMouseY);
//	}
//	else {
//		camera.LookAt(xpos, ypos);
//	}
//}
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
		std::cout << "Failed to load texture" << std::endl;
	}
	return texID;
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
		std::cout << "Error!" << std::endl;
	}

	std::cout << glGetString(GL_VERSION) << std::endl;

	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glfwSetKeyCallback(window, keyCallback);
		glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBlendEquation(GL_ADD);
		glEnable(GL_DEPTH_TEST);


		GLuint frames[4] = { 
			/*loadSpriteSheet("res/images/", "frame1.png", GL_REPEAT, GL_REPEAT, GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST),
			loadSpriteSheet("res/images/", "frame2.png", GL_REPEAT, GL_REPEAT, GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST),
			loadSpriteSheet("res/images/", "frame3.png", GL_REPEAT, GL_REPEAT, GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST),
			loadSpriteSheet("res/images/", "frame4.png", GL_REPEAT, GL_REPEAT, GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST)*/
			loadSpriteSheet("res/images/", "newcow.png", GL_REPEAT, GL_REPEAT, GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST),
			loadSpriteSheet("res/images/", "newcow.png", GL_REPEAT, GL_REPEAT, GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST),
			loadSpriteSheet("res/images/", "newcow.png", GL_REPEAT, GL_REPEAT, GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST),
			loadSpriteSheet("res/images/", "newcow.png", GL_REPEAT, GL_REPEAT, GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST)
		};
		GLuint bckgrnd = loadSpriteSheet("res/images/", "backgroundrgba1.png", GL_REPEAT, GL_REPEAT, GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST);
		GLuint sphereCow = loadSpriteSheet("res/images/", "newcow.png", GL_REPEAT, GL_REPEAT, GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST);
		GLuint letters = loadSpriteSheet("res/images/", "Letters.png", GL_REPEAT, GL_REPEAT, GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST);

		CollidableSprite player = CollidableSprite(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(-0.25f, -0.5f), glm::vec2(0.25f, 0.5f), glm::vec2(-0.5f, -0.5f), glm::vec2(0.5f, 0.5f), 0.0f, glm::vec2(0.0f, 0.9375f), glm::vec2(0.0625f, 1.0f), frames[0], 0, 1.0f, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, glm::vec3(0.0f, 0.0f, 0.0f), 1.0f);
		Object background = Object(type::rectangle, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(-50.0f, -50.0f), glm::vec2(50.0f, 50.0), -1.0f, glm::vec2(0.0f, 0.0f), glm::vec2(10.0f, 10.0f), bckgrnd);
		Object aLetter = Object(type::rectangle, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(-0.5f, -1.0f), glm::vec2(0.5f, 1.0f), 1.0f, glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), letters);
		//CollidableSprite ground = CollidableSprite(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(-2.5f, -2.5f), glm::vec2(2.5f, -2.0f), 0.0f, glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), sphereCow, 0, 1.0f, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, glm::vec3(0.0f, 0.0f, 0.0f));
		CollidableSprite ground[] = {
			CollidableSprite(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(-0.5f, -0.5f), glm::vec2(0.5f, 0.5f), 0.0f, glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), sphereCow, 0, 1.0f, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, glm::vec3(0.0f, 0.0f, 0.0f), 1.0f),
			CollidableSprite(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(-0.5f, -0.5f), glm::vec2(0.5f, 0.5f), 0.0f, glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), sphereCow, 0, 1.0f, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, glm::vec3(0.0f, 0.0f, 0.0f), 1.0f),
			CollidableSprite(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(2.0f, 0.0f, 0.0f), glm::vec2(-0.5f, -0.5f), glm::vec2(0.5f, 0.5f), 0.0f, glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), sphereCow, 0, 1.0f, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, glm::vec3(0.0f, 0.0f, 0.0f), 1.0f),
			CollidableSprite(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(3.0f, 0.0f, 0.0f), glm::vec2(-0.5f, -0.5f), glm::vec2(0.5f, 0.5f), 0.0f, glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), sphereCow, 0, 1.0f, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, glm::vec3(0.0f, 0.0f, 0.0f), 1.0f),
			CollidableSprite(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(4.0f, 0.0f, 0.0f), glm::vec2(-0.5f, -0.5f), glm::vec2(0.5f, 0.5f), 0.0f, glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), sphereCow, 0, 1.0f, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, glm::vec3(0.0f, 0.0f, 0.0f), 1.0f)
		};
		//CollidableSprite(glm::vec3 rot, glm::vec3 trans, glm::vec2 minExtents, glm::vec2 maxExtents, float z, glm::vec2 bottomLeftTexCoord, glm::vec2 topRightTexCoord, GLuint & tex, GLuint startingFrame, float m, glm::vec3 linearVel, glm::vec3 angularVel, glm::vec3 f, glm::vec3 t, float MOI, glm::vec3 gravity, float COR)


		ImGui::CreateContext();
		ImGui_ImplGlfwGL3_Init(window, false);
		ImGui::StyleColorsDark();

		glm::vec3 cameraTranslation(0.0f, 0.0f, 0.0f);
		glfwSetCursorPos(window, 0.0, 0.0);

		float timeConstant = 1.0f;
		
		Timer spriteTimer = Timer(0.25f);
		spriteTimer.Start();
		Timer lungeTimer = Timer(2.5f);

		double lastTime = glfwGetTime();
		double deltaT = 0, nowTime = 0;
		bool lungeReady = true;
		bool movementPaused = false;
		
		while (!glfwWindowShouldClose(window))
		{
			nowTime = glfwGetTime();
			deltaT = (nowTime - lastTime);
			lastTime = nowTime;

			glClearColor(0.3f, 0.7f, 0.95f, 1.0f);
			glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
			ImGui_ImplGlfwGL3_NewFrame();

			float deltaTime = (float)deltaT * timeConstant;

			if (!movementPaused) {
				if (wPressed) {
					camera.MoveForward();
				}
				if (sPressed) {
					camera.MoveBackward();
				}
				if (aPressed) {
					if (player.GetLinearVelocity().x > 0) {
						player.ApplyLinearVelocity(glm::vec3(-movementSpeed, 0.0f, 0.0f));
					}
					else {
						camera.StrafeLeft(player);
					}
				}
				if (dPressed) {
					if (player.GetLinearVelocity().x > 0) {
						player.ApplyLinearVelocity(glm::vec3(movementSpeed, 0.0f, 0.0f));
					}
					else {
						camera.StrafeRight(player);
					}
				}
				if (spacePressed) {
					if (player.GetCanJump()) {
						//player.SetCanJump(false);
						//player.ApplyLinearVelocity(glm::vec3(0.0f, 5.0f, 0.0f));
						player.TranslateAdd3f(0.0f, movementSpeed, 0.0f);
					}
				}
				if (controlPressed) {
					player.TranslateAdd3f(0.0f, -movementSpeed, 0.0f);
				}
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
			if (!tPressed) {
				camera.Follow(player);
			}
			else {
				camera.Follow(player);
				printf("---------------------------------------------------------------------------------------------------------------------------\n");
				printf("                                    !T PRESSED!\n");
				printf("---------------------------------------------------------------------------------------------------------------------------\n");
				//camera.Unfollow();
			}

			///////////////////////////////////////////////////////////////////////////
			camera.ChangeMovementSpeed(movementSpeed);
			///////////////////////////////////////////////////////////////////////////
			glm::mat4 viewMatrix = camera.GetViewTransformMatrix();
			glm::mat4 projectionMatrix;
			if (currentWidth > 0 && currentHeight > 0) {
				projectionMatrix = glm::perspective(glm::radians(FOV), (float)currentWidth / (float)currentHeight, 0.1f, 10.0f);
			}
			///////////////////////////////////////////////////////////////////////////
			background.Draw(viewMatrix, projectionMatrix);
			///////////////////////////////////////////////////////////////////////////
			spriteTimer.ElapseTime(deltaTime);
			if (spriteTimer.HasFinished()) {
				player.Play(frames);
				spriteTimer.Reset(0.25f);
				spriteTimer.Start();
			}
			lungeTimer.ElapseTime(deltaTime);
			if (lungeTimer.HasFinished()) {
				lungeReady = true;
				lungeTimer.Reset(2.5f);
			}
			///////////////////////////////////////////////////////////////////////////
			for (unsigned int i = 0; i < 5; i++) {
				ground[i].Draw(viewMatrix, projectionMatrix);
			}
			///////////////////////////////////////////////////////////////////////////
			player.Draw(viewMatrix, projectionMatrix);
			player.UpdateCollision(deltaTime, ground, 5);
			///////////////////////////////////////////////////////////////////////////
			aLetter.Draw(viewMatrix, projectionMatrix);
			///////////////////////////////////////////////////////////////////////////

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