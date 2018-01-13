#include <WorldMap.hpp>
#include "GrassFloor.h"

const static std::string grassTexturePath = "../res/pic/grass.jpeg";

GrassFloor::GrassFloor(const glm::mat4 &up, const WorldMap& map, int length, int width, float size) : Component(up), length(length), width(width),
		size(size), plane(grassTexturePath), map(map), floor(up, map, 0, length, width, size)
{
	plane.material.diffuse = glm::vec3(0.5, 0.1, 0.8);
	plane.material.specular = glm::vec3(0.5, 0.1, 0.8);
	plane.material.ambient = glm::vec3(0.5, 0.1, 0.8);
}

void GrassFloor::render(const Shader &shader, const Camera &camera)
{

	glm::mat4 mat = glm::scale(this->modelMatrix, glm::vec3(size, size, size));
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < length; j++)
		{
			if(map.hasLake(i, j))continue;
			plane.modelMatrix = glm::scale(mat, glm::vec3(size, size, 1));
			plane.modelMatrix = glm::translate(plane.modelMatrix, glm::vec3(i - width / 2, j - length / 2, 0));

			// plane 默认2x2...，这利缩小改为1xq
			plane.modelMatrix = glm::scale(plane.modelMatrix, glm::vec3(0.5, 0.5, 1));
			plane.render(shader, camera);
		}
	}
	floor.modelMatrix = this->modelMatrix;
	floor.render(shader, camera);
}
