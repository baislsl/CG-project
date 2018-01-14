#include <GrassPlane.h>
#include <GrassFloor.h>
#include <GrassCube.h>
#include <Prism.hpp>
#include "GameManager.h"
#include "../game/WorldMap.hpp"

GameManager::GameManager(int width, int height, GLFWwindow *window)
		: width(width), height(height),
		  window(window),
		  camera(),
		  cursor(window, &camera),
		  keyBoard(window, &camera),
		  resizeManager(window),
		  shader("../res/temp.vert", "../res/temp.frag")
{
}

void GameManager::start()
{
	cursor.install();
	keyBoard.install();
	resizeManager.install();
	InputEngine::install(window);

	glfwSwapInterval(1);

	// Set initial aspect ratio
	glfwGetFramebufferSize(window, &width, &height);
	resizeManager.resizeListener(window, width, height);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
	glfwSetTime(0.0);
//	for test
	Object *tob = new Object("../res/obj/nanosuit.obj");
	tob->usingTexture = false;
	tob->material.diffuse = glm::vec3(0.5, 0.1, 0.8);
	tob->material.specular = glm::vec3(0.6, 0, 0);
	tob->material.ambient = glm::vec3(0, 0, 0.6);
	components.push_back(tob);
//	Plane *cube = new Plane("../res/Crack.bmp");
//	Sphere *cube = new Sphere(30, 30, "../res/Crack.bmp");
//	Cube *cube = new Cube("../res/Crack.bmp");
//	cube->material.diffuse = glm::vec3(0.5, 0.1, 0.8);
//	cube->material.specular = glm::vec3(0.5, 0.1, 0.8);
//	cube->material.ambient = glm::vec3(0.5, 0.1, 0.8);
//	components.push_back(cube);
//	components.push_back(cube);

//	GrassPlane floor(glm::rotate(tob->modelMatrix, glm::radians(static_cast<float >(90.0f)), glm::vec3(-1,0,0)), 0);
//	GrassFloor grass(glm::rotate(tob->modelMatrix, glm::radians(static_cast<float >(90.0f)), glm::vec3(-1, 0, 0)));
//	components.push_back(&grass);
//	Plane plane("../res/pic/x.png");
//	components.push_back(&plane);
	WorldMap worldMap;
	components.push_back(&worldMap);
//	GrassCube grassCube;
//	grassCube.modelMatrix = glm::translate(grassCube.modelMatrix, glm::vec3(0, 0.5, 0));
//	components.push_back(&grassCube);

	tob->modelMatrix = glm::scale(tob->modelMatrix,
								  glm::vec3(0.2f, 0.2f, 0.2f));    // it's a bit too big for our scene, so scale it down


	while (!glfwWindowShouldClose(window))
	{
		static float lastTime = 0;
		float currentTime = float(glfwGetTime());
		deltaTime = (currentTime - lastTime)*5;
		lastTime = currentTime;
		tob->modelMatrix = glm::rotate(tob->modelMatrix, glm::radians(deltaTime * 10), glm::vec3(0, 1, 0));
		keyBoard.processInput(deltaTime);
		setLights(shader);
		glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shader.use();
		// view/projection transformations
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), resizeManager.aspectRatio, 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		shader.setMat4("projection", projection);
		shader.setMat4("view", view);

		renderAll();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}

void GameManager::setLights(const Shader &shader)
{
	light.dirLight.direction = glm::vec3(-1, -1, -1);
	light.dirLight.ambient = glm::vec3(0.05, 0.05, 0.05);
	light.dirLight.diffuse = glm::vec3(1, 1, 1);
	light.dirLight.specular = glm::vec3(1, 1, 1);

	light.pointLight[0].position = glm::vec3(0, 4, 4);
	light.pointLight[0].diffuse = glm::vec3(1, 1, 1);
	light.pointLight[0].ambient = glm::vec3(0.1, 0.1, 0.1);
	light.pointLight[0].use = false;
//	light.pointLight[0].specular = glm::vec3(1, 1, 1);

	light.setup(shader);
}

void GameManager::renderAll()
{
	for (auto &item : components)
		item->render(shader, camera);
}
