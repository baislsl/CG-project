#ifndef CGPROJECT_CORE_H
#define CGPROJECT_CORE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <camera.h>
#include <cursor.h>
#include <ResizeManager.h>
#include <KeyBoard.h>
#include <Floor.h>
#include <HumanModel.h>
#include <Fog.h>


class GameManager {
public:
	GameManager(int width, int height, GLFWwindow *window);

	void start();

private:
	GLFWwindow *window;
	int width, height;

	Camera camera;
	Cursor cursor;
	KeyBoard keyBoard;
	ResizeManager resizeManager;

	Floor floor;
	Human human;
	Fog fog;
	std::vector<Component *> components;

	void draw_scene(GLFWwindow *window, double t);

	void setup_lights();

};


#endif //CGPROJECT_CORE_H
