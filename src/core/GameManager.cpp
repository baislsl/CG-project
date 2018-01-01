#include "GameManager.h"
#include <linmath.h>
//#include <OpenGL/glext.h>

//#define GL_LIGHT_MODEL_COLOR_CONTROL_EXT                     0x81F8
//#define GL_SEPARATE_SPECULAR_COLOR_EXT                       0x81FA

GameManager::GameManager(int width, int height, GLFWwindow *window)
		: width(width), height(height),
		  window(window),
		  camera(),
		  cursor(window, &camera),
//		  keyBoard(window, &camera),
		  resizeManager(window),
		  shader("../res/temp.vert", "../res/temp.frag")
{
//	components.push_back(&floor);
//	components.push_back(&human);
//	components.push_back(&fog);
}

void GameManager::start()
{
	cursor.install();
//	keyBoard.install();
	resizeManager.install();
	InputEngine::install(window);

//	glfwMakeContextCurrent(window);
//	gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
	glfwSwapInterval(1);

	// Set initial aspect ratio
	glfwGetFramebufferSize(window, &width, &height);
	resizeManager.resizeListener(window, width, height);

//	if (glfwExtensionSupported("GL_EXT_separate_specular_color"))
//	{
//		glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL_EXT,
//					  GL_SEPARATE_SPECULAR_COLOR_EXT);
//	}

	// Set filled polygon mode as default (not wireframe)
//	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnable(GL_DEPTH_TEST);
	glfwSetTime(0.0);
//	for test
	Object *tob = new Object("../res/obj/nanosuit.obj");
	tob->usingTexture = false;
	tob->material.diffuse = glm::vec3(0.5, 0.1, 0.8);
	tob->material.specular = glm::vec3(0.6, 0, 0);
	components.push_back(tob);


	tob->modelMatrix = glm::translate(tob->modelMatrix, glm::vec3(0.0f, -1.75f,
																  0.0f)); // translate it down so it's at the center of the scene
	tob->modelMatrix = glm::scale(tob->modelMatrix,
								  glm::vec3(0.2f, 0.2f, 0.2f));    // it's a bit too big for our scene, so scale it down
	while (!glfwWindowShouldClose(window))
	{
		static float lastTime = 0;
		float currentTime = float(glfwGetTime());
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;
		tob->modelMatrix = glm::rotate(tob->modelMatrix, glm::radians(deltaTime * 10), glm::vec3(0, 1, 0));
		processInput(window);

		glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shader.use();
		// view/projection transformations
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), resizeManager.aspectRatio, 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		shader.setMat4("projection", projection);
		shader.setMat4("view", view);
		setLights();
		renderAll();
//		drawScene(window, glfwGetTime());
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}

void GameManager::setLights()
{
	light.dirLight.direction = glm::vec3(0, -1, 0);
	light.dirLight.ambient = glm::vec3(0.1, 0, 0.1);
	light.dirLight.diffuse = glm::vec3(0.2, 0.2, 0.2);
	light.dirLight.specular = glm::vec3(1, 1, 1);

	light.pointLight[0].position = glm::vec3(0, 0, 10);
	light.pointLight[0].diffuse = glm::vec3(1, 1, 1);
	light.pointLight[0].ambient = glm::vec3(0.1, 0.1, 0.1);
	light.pointLight[0].specular = glm::vec3(1, 1, 1);

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

//void GameManager::drawScene(GLFWwindow *window, double t)
//{
//	mat4x4 projection;
//	mat4x4_perspective(projection,
//					   65.f * (float) M_PI / 180.f,
//					   resizeManager.aspectRatio,
//					   1.0, 60.0);
//	glClearColor(0.1f, 0.1f, 0.1f, 1.f);
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//	glMatrixMode(GL_PROJECTION);
//	glLoadMatrixf((const GLfloat *) projection);
//
//	// Setup camera
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//	glFrontFace(GL_CCW);
//	glCullFace(GL_BACK);
//	glEnable(GL_CULL_FACE);
//	glEnable(GL_LIGHTING);
//	glEnable(GL_FOG);
//	glEnable(GL_DEPTH_TEST);
//
//	camera.render();
//	setup_lights();
//
//	for (auto c : components)
//	{
//		c->render();
//	}
//
//
//	glDisable(GL_LIGHTING);
//	glDisable(GL_FOG);
//
//	// Particles must be drawn after all solid objects have been drawn
////	 draw_particles(window, t, dt);
//
//	// Z-buffer not needed anymore
////	glDisable(GL_DEPTH_TEST);
//}
//
//void GameManager::setup_lights()
//{
//	float l1pos[4], l1amb[4], l1dif[4], l1spec[4];
//	float l2pos[4], l2amb[4], l2dif[4], l2spec[4];
//
//	// Set light source 1 parameters
//	l1pos[0] = 0.f;
//	l1pos[1] = -9.f;
//	l1pos[2] = 8.f;
//	l1pos[3] = 1.f;
//	l1amb[0] = 0.2f;
//	l1amb[1] = 0.2f;
//	l1amb[2] = 0.2f;
//	l1amb[3] = 1.f;
//	l1dif[0] = 0.8f;
//	l1dif[1] = 0.4f;
//	l1dif[2] = 0.2f;
//	l1dif[3] = 1.f;
//	l1spec[0] = 1.f;
//	l1spec[1] = 0.6f;
//	l1spec[2] = 0.2f;
//	l1spec[3] = 0.f;
//
//	// Set light source 2 parameters
//	l2pos[0] = -15.f;
//	l2pos[1] = 12.f;
//	l2pos[2] = 1.5f;
//	l2pos[3] = 1.f;
//	l2amb[0] = 0.f;
//	l2amb[1] = 0.f;
//	l2amb[2] = 0.f;
//	l2amb[3] = 1.f;
//	l2dif[0] = 0.2f;
//	l2dif[1] = 0.4f;
//	l2dif[2] = 0.8f;
//	l2dif[3] = 1.f;
//	l2spec[0] = 0.2f;
//	l2spec[1] = 0.6f;
//	l2spec[2] = 1.f;
//	l2spec[3] = 0.f;
//
//	glLightfv(GL_LIGHT1, GL_POSITION, l1pos);
//	glLightfv(GL_LIGHT1, GL_AMBIENT, l1amb);
//	glLightfv(GL_LIGHT1, GL_DIFFUSE, l1dif);
//	glLightfv(GL_LIGHT1, GL_SPECULAR, l1spec);
//	glLightfv(GL_LIGHT2, GL_POSITION, l2pos);
//	glLightfv(GL_LIGHT2, GL_AMBIENT, l2amb);
//	glLightfv(GL_LIGHT2, GL_DIFFUSE, l2dif);
//	glLightfv(GL_LIGHT2, GL_SPECULAR, l2spec);
//
//	glEnable(GL_LIGHT1);
//	glEnable(GL_LIGHT2);
//}
