#include "GameEntry.h"

void GameEntry::run() {
	int width = 640, height = 480;
	if (!glfwInit()) {
		fprintf(stderr, "Failed to initialize GLFW\n");
		exit(EXIT_FAILURE);
	}
	GLFWwindow *window = glfwCreateWindow(width, height, "Particle Engine", NULL, NULL);
	if (!window) {
		fprintf(stderr, "Failed to create GLFW window\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	GameManager game(width, height, window);
	game.start();
}
