#include "GrassPlane.h"
#include "WorldMap.hpp"
#include <random>

GrassPlane::GrassPlane(const glm::mat4 &up, const WorldMap& map, double z, int length, int width, float size) : Component(up), map(map), z(z), length(length),
		width(width), size(size),
		squares({GrassSquare(*this, "../res/3ds/floor/grass_1msq_normal_01.3ds", this->modelMatrix, size),
				 GrassSquare(*this, "../res/3ds/floor/grass_1msq_normal_02.3ds", this->modelMatrix, size),
				 GrassSquare(*this, "../res/3ds/floor/grass_1msq_normal_03.3ds", this->modelMatrix, size),
				 GrassSquare(*this, "../res/3ds/floor/grass_1msq_normal_04.3ds", this->modelMatrix, size),
				 GrassSquare(*this, "../res/3ds/floor/grass_1msq_normal_05.3ds", this->modelMatrix, size)})
{
	this->modelMatrix = glm::translate(this->modelMatrix, glm::vec3(0, 0, z));
	this->modelMatrix = glm::scale(this->modelMatrix, glm::vec3(size, size, size));
	std::default_random_engine e;
	std::uniform_int_distribution<unsigned> u(0, squares.size() - 1);
	std::uniform_int_distribution<unsigned> u2(0, width);
	std::uniform_int_distribution<unsigned> u3(0, length);
	squareTypes.resize(width);
	for(auto& i : squareTypes) i.resize(length);
	static int mask[][2] = {
			{0,  1}, {0,  -1}, {0,  0},
			{1,  1}, {1,  -1}, {1,  0},
			{-1, 1}, {-1, -1}, {-1, 0},
	};
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < length; j++)
		{
			squareTypes[i][j] = squares.size();
		}
	}
	int count = width*length / 100;
	while (count --){
		int i = u2(e), j = u3(e), type = u(e);
		for (int k = 0; k < 9; k++)
		{
			if (i + mask[k][0] >= 0 && i + mask[k][0] < width && j + mask[k][0] >= 0 && j + mask[k][0] < length)
				squareTypes[i + mask[k][0]][j + mask[k][1]] = static_cast<unsigned >(type);
		}
	}

}

void GrassPlane::render(const Shader &shader, const Camera &camera)
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < length; j++)
		{
			double x = i, y = j;
			if (squareTypes[i][j] == squares.size() || map.hasLake(i, j)) continue;
			squares.at(squareTypes[i][j]).renderToXY(x, y, shader, camera);
		}
	}

}

GrassPlane::GrassSquare::GrassSquare(const GrassPlane &parent, const std::string &filename, const glm::mat4 &up,
								double size) : Object(filename), parent(parent)
{
	material.diffuse = glm::vec3(0.5, 1, 0.5);
	material.specular = glm::vec3(0.5, 1, 0.5);
	material.ambient = glm::vec3(0.5, 1, 0.5);
}

void GrassPlane::GrassSquare::renderToXY(double x, double y, const Shader &shader, const Camera &camera)
{
	shader.setVec3("viewPos", camera.Position);
	shader.setVec3("material.diffuse", material.diffuse);
	shader.setVec3("material.specular", material.specular);
	shader.setVec3("material.ambient", material.ambient);
	shader.setFloat("material.shininess", material.shininess);
	shader.setBool("usingTexture", usingTexture);
	shader.setMat4("model",
				   glm::translate(parent.modelMatrix, glm::vec3(x - parent.width / 2, y - parent.length / 2, 0)));
	model.Draw(shader);
}
