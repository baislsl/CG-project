#include <functional>
#include <map>
#include "KeyBoard.h"

using eventFunc = std::function<void(GLfloat)>;

KeyBoard::KeyBoard(GLFWwindow *window, Camera *camera) : window(window), camera(camera)
{}

void KeyBoard::processInput(GLfloat deltaTime)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera->ProcessKeyboard(FORWARD, deltaTime);
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera->ProcessKeyboard(BACKWARD, deltaTime);
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera->ProcessKeyboard(LEFT, deltaTime);
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera->ProcessKeyboard(RIGHT, deltaTime);
	else if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
		camera->ProcessKeyboard(UP, deltaTime);
	else if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
		camera->ProcessKeyboard(DOWN, deltaTime);
}

void KeyBoard::keyCallBack(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if (!isPress && action == GLFW_PRESS) // 按下后第一次执行
	{
		if (key == GLFW_KEY_P)	// switch view
		{
			std::cout << "press P" << std::endl;
		}
		isPress = true;

	}
	else if (action == GLFW_RELEASE)
	{
		isPress = false;
	}

}
