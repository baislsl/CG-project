#ifndef CGPROJECT_INPUT_H
#define CGPROJECT_INPUT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <functional>
#include <vector>

namespace InputEngine
{
	static std::vector<std::function<void(GLFWwindow *, double, double)>> cursorPosListeners;
	static std::vector<std::function<void(GLFWwindow *, int, int, int, int)>> keyBoardListeners;
	static std::vector<std::function<void(GLFWwindow *, int, int)>> resizeListeners;
	static std::vector<std::function<void(GLFWwindow *, double, double)>> scrollListeners;
	static std::vector<std::function<void(GLFWwindow *, int, int, int) >> cursorButtonListeners;

	static void cursorCallBack(GLFWwindow *window, double x, double y)
	{
		for (auto &listener : cursorPosListeners)
		{
			(listener)(window, x, y);
		}
	}

	static void cursorButtonCallBack(GLFWwindow *window, int button, int action, int mods)
	{
		for (auto &listener : cursorButtonListeners)
		{
			(listener)(window, button, action, mods);
		}
	}

	static void keyBoardCallBack(GLFWwindow *window, int key, int scancode, int action, int mods)
	{
		for (auto &listener : keyBoardListeners)
		{
			(listener)(window, key, scancode, action, mods);
		}
	}

	static void resizeCallBack(GLFWwindow *window, int width, int height)
	{
		for (auto &listener : resizeListeners)
		{
			(listener)(window, width, height);
		}
	}

	static void scrollCallback(GLFWwindow *window, double xoffset, double yoffset)
	{
		for (auto &listener : scrollListeners)
		{
			(listener)(window, xoffset, yoffset);
		}
	}

	static void install(GLFWwindow *window)
	{
		glfwSetCursorPosCallback(window, InputEngine::cursorCallBack);
		glfwSetKeyCallback(window, InputEngine::keyBoardCallBack);
		glfwSetScrollCallback(window, InputEngine::scrollCallback);
		glfwSetFramebufferSizeCallback(window, InputEngine::resizeCallBack);
		glfwSetMouseButtonCallback(window, InputEngine::cursorButtonCallBack);
	}

};


#endif //CGPROJECT_INPUT_H
