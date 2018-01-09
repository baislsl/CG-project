#include "Cursor.h"
#include "Camera.h"

Cursor::Cursor(GLFWwindow *windows, Camera *camera) : windows(windows), camera(camera), firstMouse(false), fov(45.0f)
{
	std::cout << "Constructing Cursor." << std::endl;
}

void Cursor::cursorPosFun(GLFWwindow *window, double x, double y)
{
	 if(!onScroll) return;
//	camera->angle += (x - prex) / 5.0;
	if (firstMouse) // 这个bool变量初始时是设定为true的
	{
		prex = x;
		prey = y;
		firstMouse = false;
	}

	camera->setYaw(float(camera->Yaw + cursorSensitivity * (x - prex)));
	camera->setPitch(float(camera->Pitch + cursorSensitivity * (prey - y)));
	prex = x;
	prey = y;
}

void Cursor::mouseScroll(GLFWwindow *window, double xoffset, double yoffset)
{
	// TODO: seems useless ?
	if (fov >= 1.0f && fov <= 45.0f)
		fov += yoffset;
	if (fov <= 1.0f)
		fov = 1.0f;
	if (fov >= 45.0f)
		fov = 45.0f;
	camera->Zoom = float(fov);
}

void Cursor::mouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
{
	std::cout << "srcoll " << onScroll << std::endl;
	onScroll = false;
	if(action == GLFW_PRESS) {
		onScroll = true;
		firstMouse = true;
	}
}
