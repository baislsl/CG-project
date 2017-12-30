#include "cursor.h"
#include "camera.h"
#include "Input.h"
#include <functional>
#include <iostream>

Cursor::Cursor(GLFWwindow *windows, Camera *camera) : windows(windows), camera(camera) {}

void Cursor::cursorPosFun(GLFWwindow *window, double x, double y) {
	camera->angle += (x - prex) / 5.0;
	prex = x;
	prey = y;
}
