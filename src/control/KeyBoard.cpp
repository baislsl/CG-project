#include <functional>
#include <map>
#include "KeyBoard.h"

using eventFunc = std::function<void(GLfloat)>;

KeyBoard::KeyBoard(GLFWwindow *window, Camera *camera) : window(window), camera(camera)
{
	globalViewCamera.Position = glm::vec3(0, 40, 0);
	globalViewCamera.Front = glm::vec3(0, -1, 0);
	globalViewCamera.Up = glm::vec3(1, 0, 0);
	globalViewCamera.Zoom = 105;
}

void KeyBoard::processInput(GLfloat deltaTime)
{
	if (inGlobalView) return;    // disable other key when switch to global view
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
	if (!inGlobalView && action == GLFW_PRESS && key == GLFW_KEY_P) // 按下后第一次执行
	{
		lastCamera = *camera;
		*camera = globalViewCamera;
		inGlobalView = true;
	}
	else if (inGlobalView && action == GLFW_RELEASE && key == GLFW_KEY_P)    // 松开后第一次执行
	{
		*camera = lastCamera;
		inGlobalView = false;
	}

}
