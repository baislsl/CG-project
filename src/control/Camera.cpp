#include <WorldMap.hpp>
#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 up, glm::vec3 front, float zoom, float yaw, float pitch)
		: Position(position), WorldUp(up), Front(front), Yaw(yaw), Pitch(pitch),
		MovementSpeed(SPEED),
		MouseSensitivity(SENSITIVTY),
		Zoom(zoom)
{
	std::cout << "Constructing Camera." << std::endl;
	updateCameraVectors();
	std::cout << "Camera constructed." << std::endl;
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(
		glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVTY), Zoom(ZOOM)
{
	Position = glm::vec3(posX, posY, posZ);
	Collide = glm::vec3(posX, posY, posZ);
	WorldUp = glm::vec3(upX, upY, upZ);
	Yaw = yaw;
	Pitch = pitch;
	updateCameraVectors();
}

void Camera::setPosition(float posX, float posY, float posZ)
{
	Position = glm::vec3(posX, posY, posZ);
}

void Camera::movePosition(float dx, float dy, float dz)
{
	Position.x += dx;
	Position.y += dy;
	Position.z += dz;
}

void Camera::setYaw(float yaw)
{
	Yaw = yaw;
	updateCameraVectors();
}

void Camera::setPitch(float pitch)
{
	Pitch = pitch;
	if (Pitch > 89.0f) Pitch = 89.0f;
	if (Pitch < -89.0f) Pitch = -89.0f;
	updateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix() const
{
	return glm::lookAt(Position, Position + Front, Up);
}

glm::vec3 Camera::transPosition(glm::vec3 position)//输入的数据中y是高度，此函数将输入的float四舍五入成int并且返回的数据中z是高度
{
	return glm::vec3((int)(position.x+50.5),(int)(position.z+50.5),(int)(position.y+0.5));
}

void Camera::ProcessKeyboard(Camera_Movement direction, float delta)
{
	float velocity = delta;

	if (direction == FORWARD)
	{
		Collide = transPosition(Position - Front_mov * (velocity+1));
		if (map->check(Collide)&&map->check(Collide+glm::vec3(0,0,-1))){
		    Position -= Front_mov * velocity;
		}
	}
	if (direction == BACKWARD)
	{
		Collide = transPosition(Position + Front_mov * (velocity+1));
		if (map->check(Collide)&&map->check(Collide+glm::vec3(0,0,-1))){
			Position += Front_mov * velocity;
		}
	}
	if (direction == LEFT)
	{
		Collide = transPosition(Position - Right * (velocity+1));
		if (map->check(Collide)&&map->check(Collide+glm::vec3(0,0,-1))){
			Position -= Right * velocity;
		}
	}
	if (direction == RIGHT)
	{
		Collide = transPosition(Position + Right * (velocity+1));
		if (map->check(Collide)&&map->check(Collide+glm::vec3(0,0,-1))){
			Position += Right * velocity;
		}
	}
	if (direction == JUMP)
	{
		for(int i = 0; i<5; i++){
			Collide = transPosition(Position + glm::vec3(0, 1, 0) * (velocity + 1));
			if (map->check(Collide)&&map->check(Collide+glm::vec3(0,0,-1)))
			{
				Position += glm::vec3(0, 1, 0) * (velocity);
			}
		}
	}
	if (direction == UP)
	{
		Collide = transPosition(Position + glm::vec3(0, 1, 0) * (velocity + 1));
		if (map->check(Collide)&&map->check(Collide+glm::vec3(0,0,-1)))
		{
			Position += glm::vec3(0, 1, 0) * velocity;
		}
	}

	std::cout << "position=" << Position.x << ":" << Position.y << ":" << Position.z << std::endl;
}

void Camera::drop()
{
	Collide = Position + glm::vec3(0, -0.4, 0);
	if(Position.y <= 2.4){
		Position.y = 2.0;
	}
	else if (map->check(Collide+glm::vec3(0,0,-2)))
	{
		Position += glm::vec3(0, -0.4, 0);
	}
}

void Camera::place(int key)
{
	map->placeblock((Position + Front).x, (Position + Front).z,	(Position + Front).y, key);
}

void Camera::updateCameraVectors()
{
	// TODO: ??? what, 所以之前初始化的front没意义？ 
	// Calculate the new Front vector
	glm::vec3 front;
	front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	front.y = sin(glm::radians(Pitch));
	front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	Front = glm::normalize(front);
	// Also re-calculate the Right and Up vector
	Right = glm::normalize(glm::cross(Front,
									  WorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.

	Front_mov = glm::normalize(glm::cross(Right,
									      WorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.

	Up = glm::normalize(glm::cross(Right, Front));
}
