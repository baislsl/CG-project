#include "Grass.h"

//const static std::string grassTexturePath = "../res/pic/grass.jpeg";
const static std::string grassTexturePath = "../res/Crack.bmp";

Grass::Grass(const glm::mat4 &up, int length, int width, float size) : Component(up), length(length), width(width),
		size(size), plane(grassTexturePath)
{
//	plane.material.diffuse = glm::vec3(0.5, 0.1, 0.8);
//	plane.material.specular = glm::vec3(0.5, 0.1, 0.8);
//	plane.material.ambient = glm::vec3(0.5, 0.1, 0.8);
}

void Grass::render(const Shader &shader, const Camera &camera)
{

	glm::mat4 mat = glm::scale(this->modelMatrix, glm::vec3(size, size, size));

	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < width; j++)
		{
			plane.modelMatrix = glm::scale(mat, glm::vec3(size * i, size * j, 0));
			plane.render(shader, camera);
		}
	}
}