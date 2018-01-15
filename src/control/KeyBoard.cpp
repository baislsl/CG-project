#include <functional>
#include <map>
#include <glad/glad.h>
#include "KeyBoard.h"
#include <FreeImagePlus.h>

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
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera->ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera->ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera->ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera->ProcessKeyboard(RIGHT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS){
		if(isPress == false)
		{
			isPress = true;
			camera->ProcessKeyboard(JUMP, deltaTime);
		}
	}
	else if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE)
		isPress = false;
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
		camera->ProcessKeyboard(UP, deltaTime);

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

	if (action == GLFW_PRESS && key == GLFW_KEY_M)
		saveScreenShot();

}


void KeyBoard::saveScreenShot()
{
	int width, height;
	glfwGetWindowSize(window, &width, &height);

	int n = 3 * width * height;
	GLubyte *pixels = new GLubyte[n];

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, pixels);

	// Convert to FreeImage format & save to file
	FIBITMAP *image = FreeImage_ConvertFromRawBits(pixels, width, height, 3 * width, 24, 0xFF0000, 0x00FF00, 0x0000FF,
												   false);
	std::hash<double> hash;
	double time = glfwGetTime();
	std::string path = std::to_string(hash(time)) + ".bmp";
	FreeImage_Save(FIF_BMP, image, path.c_str(), 0);
	std::cout << "save screenshot in " << path << std::endl;

	// Free resources
	FreeImage_Unload(image);
	delete[] pixels;
}
