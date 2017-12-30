#ifndef CGPROJECT_INPUT_H
#define CGPROJECT_INPUT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <functional>
#include <vector>
#include <iostream>

namespace InputEngine {
	static std::vector<std::function<void(GLFWwindow *, double, double)>> cursorPosListeners;
	static std::vector<std::function<void(GLFWwindow *, int, int, int, int)>> keyBoardListeners;
	static std::vector<std::function<void(GLFWwindow *, int, int)>> resizeListeners;

	static void setCursorListener(GLFWwindow *window, double x, double y) {
		for (auto &listener : cursorPosListeners) {
			(listener)(window, x, y);
		}
	}

	static void setKeyBoardListener(GLFWwindow *window, int key, int scancode, int action, int mods) {
		for (auto &listener : keyBoardListeners) {
			(listener)(window, key, scancode, action, mods);
		}
	}

	static void setResizeListener(GLFWwindow *window, int width, int height) {
		for (auto &listener: resizeListeners) {
			(listener)(window, width, height);
		}
	}

	static void install(GLFWwindow *windows) {
		glfwSetCursorPosCallback(windows, InputEngine::setCursorListener);
		glfwSetKeyCallback(windows, InputEngine::setKeyBoardListener);
		glfwSetFramebufferSizeCallback(windows, InputEngine::setResizeListener);
	}

};


#endif //CGPROJECT_INPUT_H
