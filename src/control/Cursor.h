#ifndef CGPROJECT_CURSOR_H
#define CGPROJECT_CURSOR_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <functional>
#include "Input.h"
#include <Camera.h>

const float cursorSensitivity = 0.05;

class Cursor
{
public:
	double fov;

	explicit Cursor(GLFWwindow *windows, Camera *camera);

	void install()
	{
		std::function<void(GLFWwindow *, double, double)> mouseListener
				= std::bind(&Cursor::cursorPosFun,
							this,
							std::placeholders::_1,
							std::placeholders::_2,
							std::placeholders::_3);
		InputEngine::cursorPosListeners.push_back(mouseListener);
		std::function<void(GLFWwindow *, double, double)> ScrollListener
				= std::bind(&Cursor::mouseScroll,
							this,
							std::placeholders::_1,
							std::placeholders::_2,
							std::placeholders::_3);
		InputEngine::scrollListeners.push_back(ScrollListener);
		std::function<void(GLFWwindow*, int, int, int)> mouseButtonListener
				= std::bind(&Cursor::mouseButtonCallback,
							this,
							std::placeholders::_1,
							std::placeholders::_2,
							std::placeholders::_3,
							std::placeholders::_4);
		InputEngine::cursorButtonListeners.push_back(mouseButtonListener);
	}

private:
	GLFWwindow *windows;
	Camera *camera;
	double prex;
	double prey;
	bool firstMouse;
	bool onScroll;

	void cursorPosFun(GLFWwindow *window, double x, double y);

	void mouseScroll(GLFWwindow *window, double xoffset, double yoffset);

	void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

};


#endif // CGPROJECT_CURSOR_H
