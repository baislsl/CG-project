#ifndef CGPROJECT_CAMERA_H
#define CGPROJECT_CAMERA_H


#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


#include <iostream>
#include <vector>

class WorldMap;
// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement
{
	FORWARD, BACKWARD, LEFT, RIGHT, JUMP, UP, DOWN
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
	glm::vec3 Collide;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 Front_mov;
	glm::vec3 WorldUp;
	// Eular Angles
	float Yaw;
	float Pitch;
	// Camera options
	float MovementSpeed;
	float MouseSensitivity;
	float Zoom;
	float speed;
	bool enableDrop = true;

	WorldMap *map;

	// Constructor with vectors
	explicit Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
					glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
					glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f),
					float zoom = ZOOM, float yaw = YAW, float pitch = PITCH);

	// Constructor with scalar values
	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

	void setPosition(float posX, float posY, float posZ);

	void movePosition(float dx, float dy, float dz);

	glm::vec3 transPosition(glm::vec3 position) const ;

	glm::tvec3<size_t > getCurrentPosition() const
	{
		return transPosition(Position);
	}

	void setYaw(float yaw);

	void setPitch(float pitch);

	void drop();

	void place(int key);

	glm::vec3 nextPlacePosition() const ;

	glm::vec3 targetboxPosition() const ;

	// Returns the view matrix calculated using Eular Angles and the LookAt Matrix
	glm::mat4 GetViewMatrix() const;

//	// Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
	void ProcessKeyboard(Camera_Movement direction, float delta);

private:
	// Calculates the front vector from the Camera's (updated) Eular Angles
	void updateCameraVectors();
};

#endif //CGPROJECT_CAMERA_H
