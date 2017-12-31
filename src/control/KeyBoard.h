#ifndef CGPROJECT_KEYBOARD_H
#define CGPROJECT_KEYBOARD_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <functional>
#include "Input.h"
#include "Camera.h"

class Camera;

class KeyBoard
{
public:
	KeyBoard(GLFWwindow *window, Camera *camera);

	void install()
	{
		std::function<void(GLFWwindow *, int, int, int, int)> function =
				std::bind(&KeyBoard::keyCallBack,
						  this,
						  std::placeholders::_1,
						  std::placeholders::_2,
						  std::placeholders::_3,
						  std::placeholders::_4,
						  std::placeholders::_5);
		InputEngine::keyBoardListeners.emplace_back(function);
	}


private:
	GLFWwindow *window;
	Camera *camera;
	float lastPressTime;

	void keyCallBack(GLFWwindow *window, int key, int scancode, int action, int mods);

};


#endif //CGPROJECT_KEYBOARD_H
