#ifndef CGPROJECT_CURSOR_H
#define CGPROJECT_CURSOR_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <functional>
#include "Input.h"

class Camera;

class Cursor {
public:
	explicit Cursor(GLFWwindow *windows, Camera *camera);

	void install() {
		std::function<void(GLFWwindow *, double, double)> mouseListener
				= std::bind(&Cursor::cursorPosFun,
							this,
							std::placeholders::_1,
							std::placeholders::_2,
							std::placeholders::_3);
		InputEngine::cursorPosListeners.push_back(mouseListener);
	}

private:
	GLFWwindow *windows;
	Camera *camera;
	double prex;
	double prey;

	void cursorPosFun(GLFWwindow *window, double x, double y);
};


#endif // CGPROJECT_CURSOR_H
