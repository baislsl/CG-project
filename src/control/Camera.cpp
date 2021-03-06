#include <WorldMap.hpp>
#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 up, glm::vec3 front, float zoom, float yaw, float pitch) : Position(
		position), WorldUp(up), Front(front), Yaw(yaw), Pitch(pitch), MovementSpeed(SPEED),
		MouseSensitivity(SENSITIVTY), Zoom(zoom), speed(0)
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

glm::vec3 Camera::transPosition(glm::vec3 position) const //输入的数据中y是高度，此函数将输入的float四舍五入成int并且返回的数据中z是高度
{
	return glm::vec3(std::round(position.x + map->width / 2), std::round(position.z + map->length / 2),
					 std::round(position.y));
}

void Camera::ProcessKeyboard(Camera_Movement direction, float delta)
{
	float velocity = delta;

	if (direction == FORWARD)
	{
		Collide = transPosition(Position - Front_mov * (velocity + 1));
		if (Collide.x >= 100 || Collide.x <= 0 || Collide.y >= 100 || Collide.y <= 0);
		else if (map->check(Collide) && map->check(Collide + glm::vec3(0, 0, -1)) &&
				 map->check(Collide + glm::vec3(0, 0, -2)))
		{
			Collide = transPosition(Position - Front_mov * velocity);
			if (map->check(Collide) && map->check(Collide + glm::vec3(0, 0, -1)) &&
				map->check(Collide + glm::vec3(0, 0, -2)))
			{
				Position -= Front_mov * velocity;
			}
		}
	}
	if (direction == BACKWARD)
	{
		Collide = transPosition(Position + Front_mov * (velocity + 1));
		if (Collide.x >= 100 || Collide.x <= 0 || Collide.y >= 100 || Collide.y <= 0);
		else if (map->check(Collide) && map->check(Collide + glm::vec3(0, 0, -1)) &&
				 map->check(Collide + glm::vec3(0, 0, -2)))
		{
			Collide = transPosition(Position + Front_mov * velocity);
			if (map->check(Collide) && map->check(Collide + glm::vec3(0, 0, -1)) &&
				map->check(Collide + glm::vec3(0, 0, -2)))
			{
				Position += Front_mov * velocity;
			}
		}
	}
	if (direction == LEFT)
	{
		Collide = transPosition(Position - Right * (velocity + 1));
		if (Collide.x >= 100 || Collide.x <= 0 || Collide.y >= 100 || Collide.y <= 0);
		else if (map->check(Collide) && map->check(Collide + glm::vec3(0, 0, -1)) &&
				 map->check(Collide + glm::vec3(0, 0, -2)))
		{
			Collide = transPosition(Position - Right * velocity);
			if (map->check(Collide) && map->check(Collide + glm::vec3(0, 0, -1)) &&
				map->check(Collide + glm::vec3(0, 0, -2)))
			{
				Position -= Right * velocity;
			}
		}
	}
	if (direction == RIGHT)
	{
		Collide = transPosition(Position + Right * (velocity + 1));
		if (Collide.x >= 100 || Collide.x <= 0 || Collide.y >= 100 || Collide.y <= 0);
		else if (map->check(Collide) && map->check(Collide + glm::vec3(0, 0, -1)) &&
				 map->check(Collide + glm::vec3(0, 0, -2)))
		{
			Collide = transPosition(Position + Right * velocity);
			if (map->check(Collide) && map->check(Collide + glm::vec3(0, 0, -1)) &&
				map->check(Collide + glm::vec3(0, 0, -2)))
			{
				Position += Right * velocity;
			}
		}
	}
	if (direction == JUMP)
	{
		Collide = transPosition(Position + glm::vec3(0, 3, 0));
		if (Collide.z >= 20);
		else if (map->check(Collide) && map->check(Collide + glm::vec3(0, 0, -1)))
		{
			Position += glm::vec3(0, 3, 0);
		}
		/*if (map->check(Position + glm::vec3(0, 1, 0))) speed += 1;
		std::cout << "jump, speed:" << speed << std::endl;*/
	}
	if (direction == UP)
	{
		Collide = transPosition(Position + glm::vec3(0, 1, 0) * (velocity + 1));
		if (map->check(Collide) && map->check(Collide + glm::vec3(0, 0, -1)))
		{
			Position += glm::vec3(0, 1, 0) * velocity;
		}
	}
}

void Camera::drop()
{
	if (!this->enableDrop)
		return;
	Collide = transPosition(Position + glm::vec3(0, -0.2, 0));
	/*speed -= 0.1;
	if (speed < -1) speed = -1;
	if (Position.y <= 2.2 && speed < 0) speed = 0;

	std::cout << "speed:" << speed << std::endl;
	Collide = transPosition(Position + glm::vec3(0, speed, 0));
	if (map->check(Collide)&&map->check(Collide + glm::vec3(0, 0, -2)) && map->check(Collide + glm::vec3(0, 0, -1)))
		Position += glm::vec3(0, speed, 0);
	else
		Position.y = (int)Position.y;*/
	if (Position.y <= 2.2)
	{
		Position.y = 2.0;
	}
	else if (map->check(Collide + glm::vec3(0, 0, -2)) && map->check(Collide + glm::vec3(0, 0, -1)))
	{
		Position += glm::vec3(0, -0.2, 0);
	}
}

void Camera::place(int key)
{
	glm::vec3 pos;
	pos = nextPlacePosition();
	map->placeblock(pos, key);
//	std::cout << "pos: x=" << pos.x << ",y=" << pos.y << ",z=" << pos.z << std::endl;
}

glm::vec3 Camera::nextPlacePosition() const
{
	auto v3 = Position + Front + Front + Front + Front + Front;
	return transPosition(glm::tvec3<int>(static_cast<int>(v3.x), static_cast<int>(v3.y), static_cast<int>(v3.z)));
}

glm::vec3 Camera::targetboxPosition() const
{
	auto v3 = Front + Front + Front + Front + Front;
	return transPosition(glm::tvec3<int>(static_cast<int>(v3.x), static_cast<int>(v3.y), static_cast<int>(v3.z)));
}


void Camera::updateCameraVectors()
{
	// TODO: ??? what, 所以之前初始化的front没意义？
	// Calculate the new Front vector
	glm::vec3 front;
	front.x = cosf(glm::radians(Yaw)) * cosf(glm::radians(Pitch));
	front.y = sinf(glm::radians(Pitch));
	front.z = sinf(glm::radians(Yaw)) * cosf(glm::radians(Pitch));
	Front = glm::normalize(front);
	// Also re-calculate the Right and Up vector
	Right = glm::normalize(glm::cross(Front,
									  WorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.

	Front_mov = glm::normalize(glm::cross(Right,
										  WorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.

	Up = glm::normalize(glm::cross(Right, Front));
}
