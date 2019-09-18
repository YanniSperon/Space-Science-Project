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
#include "AxisAlignedBoundingBox.h"
#include "Plane.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/euler_angles.hpp"
#include "glm/gtx/quaternion.hpp"
#include "primitives/Vertex.h"
#include "primitives/ShapeGenerator.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"

// https://www.youtube.com/watch?v=fUO9tk6IarY&list=PLEETnX-uPtBXm1KEr_2zQ6K_0hoGH6JJ0&index=7 - 00:31

Config config = Config("", "config.txt");

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
static float movementSpeed = 0.1f;

Camera camera = Camera(true, movementSpeed, glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 5.0f), mouseSensitivity);

static int initialWidth = config.getInitialWidthPreference();
static int initialHeight = config.getInitialHeightPreference();

static int currentWidth = initialWidth;
static int currentHeight = initialHeight;

static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_W && action == GLFW_PRESS) {
		wPressed = true;
	}
	else if (key == GLFW_KEY_W && action == GLFW_RELEASE) {
		wPressed = false;
	}

	if (key == GLFW_KEY_S && action == GLFW_PRESS) {
		sPressed = true;
	}
	else if (key == GLFW_KEY_S && action == GLFW_RELEASE) {
		sPressed = false;
	}



	if (key == GLFW_KEY_A && action == GLFW_PRESS) {
		aPressed = true;
	}
	else if (key == GLFW_KEY_A && action == GLFW_RELEASE) {
		aPressed = false;
	}

	if (key == GLFW_KEY_D && action == GLFW_PRESS) {
		dPressed = true;
	}
	else if (key == GLFW_KEY_D && action == GLFW_RELEASE) {
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
		movementSpeed *= 2;
	}
	else if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_RELEASE) {
		movementSpeed /= 2;
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
		/*if (glfwRawMouseMotionSupported())
			glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
		glfwSetCursorPosCallback(window, cursorPositionCallback);*/
		glfwSetKeyCallback(window, keyCallback);
		glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_DEPTH_TEST);

		Object object = Object(type::blankModel, "", "plane.obj", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -3.0f, -3.0f));

		PhysicsBody player = PhysicsBody(type::cubeModel, "", "", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), "", "cow.png",
			1.0f, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f),
			1.0f, glm::vec3(0.0f, 0.0f, 0.0f));

		ImGui::CreateContext();
		ImGui_ImplGlfwGL3_Init(window, false);
		ImGui::StyleColorsDark();

		glm::vec3 cameraTranslation(0.0f, 0.0f, 0.0f);
		glfwSetCursorPos(window, 0.0, 0.0);

		float timeConstant = 1.0f;
		float currentTime = 0.0f;
		
		while (!glfwWindowShouldClose(window))
		{
			glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
			ImGui_ImplGlfwGL3_NewFrame();


			if (wPressed) {
				camera.MoveForward();
			}
			if (sPressed) {
				camera.MoveBackward();
			}
			if (aPressed) {
				camera.StrafeLeft();
			}
			if (dPressed) {
				camera.StrafeRight();
			}
			if (spacePressed) {
				camera.MoveUp();
			}
			if (controlPressed) {
				camera.MoveDown();
			}

			///////////////////////////////////////////////////////////////////////////
			camera.ChangeMovementSpeed(movementSpeed);
			camera.BringWith(player);
			
			glm::mat4 viewMatrix = camera.GetViewTransformMatrix();
			glm::mat4 projectionMatrix;
			if (currentWidth > 0 && currentHeight > 0) {
				projectionMatrix = glm::perspective(glm::radians(FOV), (float)currentWidth / (float)currentHeight, 0.1f, 100.0f);
			}
			///////////////////////////////////////////////////////////////////////////
			object.Draw(viewMatrix, projectionMatrix);
			///////////////////////////////////////////////////////////////////////////
			player.Draw(viewMatrix, projectionMatrix);
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