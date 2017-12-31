#include "Cursor.h"
#include "Camera.h"

Cursor::Cursor(GLFWwindow *windows, Camera *camera) : windows(windows), camera(camera) {}

void Cursor::cursorPosFun(GLFWwindow *window, double x, double y) {
	camera->angle += (x - prex) / 5.0;
	prex = x;
	prey = y;
}
