#ifndef CGPROJECT_CORE_H
#define CGPROJECT_CORE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Camera.h>
#include <Cursor.h>
#include <ResizeManager.h>
#include <Floor.h>
#include <HumanModel.h>
#include <Fog.h>
#include <Shader.h>
#include <Object.h>
#include <cstring>

class GameManager
{
public:
	GameManager(int width, int height, GLFWwindow *window);

	void start();

private:
	GLFWwindow *window;
	int width, height;
	float deltaTime;

	Camera camera;
	Cursor cursor;
	ResizeManager resizeManager;

	Shader shader;

	std::vector<Component *> components;
	std::vector<Object *> objects;


	void renderAll();

	void processInput(GLFWwindow *window);


};


#endif //CGPROJECT_CORE_H
