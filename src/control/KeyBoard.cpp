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
				camera->translate(-1);
				break;
			case GLFW_KEY_D:
				camera->translate(1);
				break;
			case GLFW_KEY_S:
				camera->forward(-1);
				break;
			case GLFW_KEY_W:
				camera->forward(1);
				break;
			default:
				break;
		}
	}
}


