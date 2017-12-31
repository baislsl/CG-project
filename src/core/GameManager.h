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


//class Light
//{
//public:
//	float position[3];
//	float ambient[3];
//	float diffuse[3];
//	float specular[3];
//	float constant, linear, quadratic;
//
//	Light() : position({0, 0, 0}), ambient({0, 0, 0}), diffuse({0, 0, 0}), specular({0, 0, 0}), constant(0), linear(0),
//			  quadratic(0)
//	{}
//};

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
//	Floor floor;
//	Human human;
//	Fog fog;
	std::vector<Component *> components;
	std::vector<Object *> objects;


	void setLights();

	void renderAll();

	void processInput(GLFWwindow *window);

	void setup_lights();

	void drawScene(GLFWwindow *window, double t);

};


#endif //CGPROJECT_CORE_H
