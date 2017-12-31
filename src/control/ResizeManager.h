#ifndef CGPROJECT_RESIZEMANAGER_H
#define CGPROJECT_RESIZEMANAGER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <functional>
#include <Input.h>
#include <iostream>

class ResizeManager
{
public:
	explicit ResizeManager(GLFWwindow *window) : window(window)
	{
		std::cout << "Constructing ResizeManager." << std::endl;
	}

	void install()
	{
		std::function<void(GLFWwindow *, int, int)> function =
				std::bind(&ResizeManager::resizeListener,
						  this,
						  std::placeholders::_1,
						  std::placeholders::_2,
						  std::placeholders::_3);
		InputEngine::resizeListeners.emplace_back(function);
	}

	void resizeListener(GLFWwindow *window, int width, int height)
	{
		glViewport(0, 0, width, height);
		aspectRatio = height ? width / (float) height : 1.f;
		this->width = width;
		this->hegiht = height;
	}

	int width, hegiht;
	float aspectRatio;

private:
	GLFWwindow *window;


};


#endif //CGPROJECT_RESIZEMANAGER_H
