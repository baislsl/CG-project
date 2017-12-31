#include "KeyBoard.h"


KeyBoard::KeyBoard(GLFWwindow *window, Camera *camera) : window(window), camera(camera) {
}

void KeyBoard::keyCallBack(GLFWwindow *window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {
		switch (key) {
			case GLFW_KEY_ESCAPE:
				glfwSetWindowShouldClose(window, GLFW_TRUE);
				break;
			case GLFW_KEY_A:
				camera->ProcessKeyboard(Camera_Movement::LEFT, 1);
				break;
			case GLFW_KEY_D:
				camera->ProcessKeyboard(Camera_Movement::RIGHT, 1);
				break;
			case GLFW_KEY_S:
				camera->ProcessKeyboard(Camera_Movement::BACKWARD, 1);
				break;
			case GLFW_KEY_W:
				camera->ProcessKeyboard(Camera_Movement::FORWARD, 1);
				break;
			default:
				break;
		}
	}
	if (action == GLFW_REPEAT)
	{
		float delta = glfwGetTime() - lastPressTime;
		switch (key) {
			case GLFW_KEY_ESCAPE:
				glfwSetWindowShouldClose(window, GLFW_TRUE);
				break;
			case GLFW_KEY_A:
				camera->ProcessKeyboard(Camera_Movement::LEFT, delta);
				break;
			case GLFW_KEY_D:
				camera->ProcessKeyboard(Camera_Movement::RIGHT, delta);
				break;
			case GLFW_KEY_S:
				camera->ProcessKeyboard(Camera_Movement::BACKWARD, delta);
				break;
			case GLFW_KEY_W:
				camera->ProcessKeyboard(Camera_Movement::FORWARD, delta);
				break;
			default:
				break;
		}
	}
	lastPressTime = float(glfwGetTime());
}


