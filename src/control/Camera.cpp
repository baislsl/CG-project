
#include "Camera.h"
#include <complex>
#include <GL/glu.h>

Camera::Camera(GLFWwindow *windows, double posX, double poxY, double posZ, double angle)
		: windows(windows), posX(posX), posY(poxY), posZ(posZ), angle(angle) {
}

void Camera::forward(double distance) {
	posX += distance * sin(angle);
	posY += distance * cos(angle);
}

void Camera::translate(double distance) {
	posX += distance * sin(angle + M_PI / 2);
	posY += distance * cos(angle + M_PI / 2);
}

void Camera::render() {
	gluLookAt(posX, posY, 2,
			  posX + sin(angle), posY + cos(angle), 2,
			  0, 0, 1);

}
