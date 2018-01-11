#ifndef CGPROJECT_CAMERA_H
#define CGPROJECT_CAMERA_H


#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <vector>

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVTY = 0.1f;
const float ZOOM = 45.0f;


// An abstract camera class that processes input and calculates the corresponding Eular Angles, Vectors and Matrices for use in OpenGL
class Camera
{
public:
	// Camera Attributes
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;
	// Eular Angles
	float Yaw;
	float Pitch;
	// Camera options
	float MovementSpeed;
	float MouseSensitivity;
	float Zoom;

	// Constructor with vectors
	explicit Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
					glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
					glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f),
					float zoom = ZOOM, float yaw = YAW, float pitch = PITCH);

	// Constructor with scalar values
	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

	void setPosition(float posX, float posY, float posZ);

	void movePosition(float dx, float dy, float dz);

	void setYaw(float yaw);

	void setPitch(float pitch);


	// Returns the view matrix calculated using Eular Angles and the LookAt Matrix
	glm::mat4 GetViewMatrix();

//	// Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
	void ProcessKeyboard(Camera_Movement direction, float delta);
//
//	// Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
//	void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
//	{
//		xoffset *= MouseSensitivity;
//		yoffset *= MouseSensitivity;
//
//		Yaw += xoffset;
//		Pitch += yoffset;
//
//		// Make sure that when pitch is out of bounds, screen doesn't get flipped
//		if (constrainPitch)
//		{
//			if (Pitch > 89.0f)
//				Pitch = 89.0f;
//			if (Pitch < -89.0f)
//				Pitch = -89.0f;
//		}
//
//		// Update Front, Right and Up Vectors using the updated Eular angles
//		updateCameraVectors();
//	}
//
//	// Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
//	void ProcessMouseScroll(float yoffset)
//	{
//		if (Zoom >= 1.0f && Zoom <= 45.0f)
//			Zoom -= yoffset;
//		if (Zoom <= 1.0f)
//			Zoom = 1.0f;
//		if (Zoom >= 45.0f)
//			Zoom = 45.0f;
//	}

private:
	// Calculates the front vector from the Camera's (updated) Eular Angles
	void updateCameraVectors();
};

#endif //CGPROJECT_CAMERA_H
