#ifndef CGPROJECT_CAMERA_H
#define CGPROJECT_CAMERA_H


#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Camera {

public:
	double posX, posY, posZ;
	double angle;

	GLFWwindow *windows;

	explicit Camera(GLFWwindow *windows, double x = 0, double poxY = 0,
					double posZ = 2, double angle = 0.0);

	virtual void forward(double distance);

	virtual void translate(double distance);

	virtual void render();

private:

};

#endif //CGPROJECT_CAMERA_H
