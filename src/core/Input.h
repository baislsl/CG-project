#ifndef CGPROJECT_INPUT_H
#define CGPROJECT_INPUT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <functional>
#include <vector>

namespace InputEngine {
	static std::vector<std::function<void(GLFWwindow *, double, double)>> cursorPosListeners;
	static std::vector<std::function<void(GLFWwindow *, int, int, int, int)>> keyBoardListeners;
	static std::vector<std::function<void(GLFWwindow *, int, int)>> resizeListeners;

	static void cursorCallBack(GLFWwindow *window, double x, double y) {
		for (auto &listener : cursorPosListeners) {
			(listener)(window, x, y);
		}
	}

	static void keyBoardCallBack(GLFWwindow *window, int key, int scancode, int action, int mods) {
		for (auto &listener : keyBoardListeners) {
			(listener)(window, key, scancode, action, mods);
		}
	}

	static void resizeCallBack(GLFWwindow *window, int width, int height) {
		for (auto &listener: resizeListeners) {
			(listener)(window, width, height);
		}
	}

	static void install(GLFWwindow *windows) {
		glfwSetCursorPosCallback(windows, InputEngine::cursorCallBack);
		glfwSetKeyCallback(windows, InputEngine::keyBoardCallBack);
		glfwSetFramebufferSizeCallback(windows, InputEngine::resizeCallBack);
	}

};


#endif //CGPROJECT_INPUT_H
