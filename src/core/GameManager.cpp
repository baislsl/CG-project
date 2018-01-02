#include "GameManager.h"

GameManager::GameManager(int width, int height, GLFWwindow *window)
		: width(width), height(height),
		  window(window),
		  camera(),
		  cursor(window, &camera),
//		  keyBoard(window, &camera),
		  resizeManager(window),
		  shader("../res/temp.vert", "../res/temp.frag")
{
}

void GameManager::start()
{
	cursor.install();
//	keyBoard.install();
	resizeManager.install();
	InputEngine::install(window);

	glfwSwapInterval(1);

	// Set initial aspect ratio
	glfwGetFramebufferSize(window, &width, &height);
	resizeManager.resizeListener(window, width, height);

	glEnable(GL_DEPTH_TEST);
	glfwSetTime(0.0);
//	for test
	Object *tob = new Object("../res/obj/nanosuit.obj");
	tob->usingTexture = false;
	tob->material.diffuse = glm::vec3(0.5, 0.1, 0.8);
	tob->material.specular = glm::vec3(0.6, 0, 0);
	tob->material.ambient = glm::vec3(0, 0, 0.6);
	components.push_back(tob);
	Sphere *cube = new Sphere(30, 30, "../res/Crack.bmp");
//	Cube *cube = new Cube("../res/Crack.bmp");
	cube->material.diffuse = glm::vec3(0.5, 0.1, 0.8);
	cube->material.specular = glm::vec3(0.5, 0.1, 0.8);
	cube->material.ambient = glm::vec3(0.5, 0.1, 0.8);
	components.push_back(cube);
	tob->modelMatrix = glm::scale(tob->modelMatrix,
								  glm::vec3(0.2f, 0.2f, 0.2f));    // it's a bit too big for our scene, so scale it down
	while (!glfwWindowShouldClose(window))
	{
		static float lastTime = 0;
		float currentTime = float(glfwGetTime());
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;
		tob->modelMatrix = glm::rotate(tob->modelMatrix, glm::radians(deltaTime * 10), glm::vec3(0, 1, 0));
		cube->modelMatrix = glm::rotate(cube->modelMatrix, glm::radians(-deltaTime * 10), glm::vec3(0, 1, 0));
		processInput(window);
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
	light.dirLight.direction = glm::vec3(0, -1, -2);
	light.dirLight.ambient = glm::vec3(0.1, 0, 0.1);
	light.dirLight.diffuse = glm::vec3(0.2, 0.2, 0.2);
	light.dirLight.specular = glm::vec3(1, 1, 1);

	light.pointLight[0].position = glm::vec3(0, 4, 4);
	light.pointLight[0].diffuse = glm::vec3(0.8, 0.8, 0.8);
	light.pointLight[0].ambient = glm::vec3(0.1, 0.1, 0.1);
	light.pointLight[0].specular = glm::vec3(0.1, 0.1, 0.1);

	light.setup(shader);
}

void GameManager::renderAll()
{
	for (auto &item : components)
		item->render(shader, camera);
}

void GameManager::processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
}
