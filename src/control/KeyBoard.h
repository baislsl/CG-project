#ifndef CGPROJECT_KEYBOARD_HPP
#define CGPROJECT_KEYBOARD_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Input.h>
#include "Camera.h"

class KeyBoard
{
public:
	KeyBoard(GLFWwindow *window, Camera *camera);

	void install()
	{
		std::function<void(GLFWwindow*,int, int, int, int)> keyListener =
				std::bind(&KeyBoard::keyCallBack,
						  this,
						  std::placeholders::_1,
						  std::placeholders::_2,
						  std::placeholders::_3,
						  std::placeholders::_4,
						  std::placeholders::_5
				);
		InputEngine::keyBoardListeners.push_back(keyListener);
	}

	void processInput(GLfloat deltaTime);

private:
	GLFWwindow *window;
	Camera *camera;
	bool isPress = false;
	Camera globalViewCamera;	// todo , initialize of this camera
	Camera lastCamera;
	bool inGlobalView = false;

	void saveScreenShot();

	void keyCallBack(GLFWwindow *window, int key, int scancode, int action, int mods);

};


#endif //CGPROJECT_KEYBOARD_HPP
