#include "GameManager.h"
#include <linmath.h>
//#include <OpenGL/glext.h>

#define GL_LIGHT_MODEL_COLOR_CONTROL_EXT                     0x81F8
#define GL_SEPARATE_SPECULAR_COLOR_EXT                       0x81FA

GameManager::GameManager(int width, int height, GLFWwindow *window)
		: width(width), height(height),
		  window(window),
		  camera(window),
		  cursor(window, &camera),
		  keyBoard(window, &camera),
		  resizeManager(window) {
	components.push_back(&floor);
	components.push_back(&human);
	components.push_back(&fog);
}

void GameManager::start() {
	cursor.install();
	keyBoard.install();
	resizeManager.install();
	InputEngine::install(window);

	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
	glfwSwapInterval(1);

	// Set initial aspect ratio
	glfwGetFramebufferSize(window, &width, &height);
	resizeManager.resizeListener(window, width, height);

	if (glfwExtensionSupported("GL_EXT_separate_specular_color")) {
		glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL_EXT,
					  GL_SEPARATE_SPECULAR_COLOR_EXT);
	}

	// Set filled polygon mode as default (not wireframe)
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glfwSetTime(0.0);

	while (!glfwWindowShouldClose(window)) {
		drawScene(window, glfwGetTime());
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}

void GameManager::drawScene(GLFWwindow *window, double t) {
	mat4x4 projection;
	mat4x4_perspective(projection,
					   65.f * (float) M_PI / 180.f,
					   resizeManager.aspectRatio,
					   1.0, 60.0);
	glClearColor(0.1f, 0.1f, 0.1f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf((const GLfloat *) projection);

	// Setup camera
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	glEnable(GL_FOG);
	glEnable(GL_DEPTH_TEST);

	camera.render();
	setup_lights();

	for (auto c : components) {
		c->render();
	}


	glDisable(GL_LIGHTING);
	glDisable(GL_FOG);

	// Particles must be drawn after all solid objects have been drawn
	// draw_particles(window, t, dt);

	// Z-buffer not needed anymore
	glDisable(GL_DEPTH_TEST);
}

void GameManager::setup_lights() {
	float l1pos[4], l1amb[4], l1dif[4], l1spec[4];
	float l2pos[4], l2amb[4], l2dif[4], l2spec[4];

	// Set light source 1 parameters
	l1pos[0] = 0.f;
	l1pos[1] = -9.f;
	l1pos[2] = 8.f;
	l1pos[3] = 1.f;
	l1amb[0] = 0.2f;
	l1amb[1] = 0.2f;
	l1amb[2] = 0.2f;
	l1amb[3] = 1.f;
	l1dif[0] = 0.8f;
	l1dif[1] = 0.4f;
	l1dif[2] = 0.2f;
	l1dif[3] = 1.f;
	l1spec[0] = 1.f;
	l1spec[1] = 0.6f;
	l1spec[2] = 0.2f;
	l1spec[3] = 0.f;

	// Set light source 2 parameters
	l2pos[0] = -15.f;
	l2pos[1] = 12.f;
	l2pos[2] = 1.5f;
	l2pos[3] = 1.f;
	l2amb[0] = 0.f;
	l2amb[1] = 0.f;
	l2amb[2] = 0.f;
	l2amb[3] = 1.f;
	l2dif[0] = 0.2f;
	l2dif[1] = 0.4f;
	l2dif[2] = 0.8f;
	l2dif[3] = 1.f;
	l2spec[0] = 0.2f;
	l2spec[1] = 0.6f;
	l2spec[2] = 1.f;
	l2spec[3] = 0.f;

	glLightfv(GL_LIGHT1, GL_POSITION, l1pos);
	glLightfv(GL_LIGHT1, GL_AMBIENT, l1amb);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, l1dif);
	glLightfv(GL_LIGHT1, GL_SPECULAR, l1spec);
	glLightfv(GL_LIGHT2, GL_POSITION, l2pos);
	glLightfv(GL_LIGHT2, GL_AMBIENT, l2amb);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, l2dif);
	glLightfv(GL_LIGHT2, GL_SPECULAR, l2spec);

	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
}
