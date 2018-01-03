#include "Floor.h"

Floor::Floor(const glm::mat4 &up, double z, int length, int width, float size) : Component(up), z(z), length(length),
		width(width), size(size),
		squares({FloorSquare(*this, "../res/3ds/floor/grass_1msq_normal_01.3ds", this->modelMatrix, size),
				 FloorSquare(*this, "../res/3ds/floor/grass_1msq_normal_02.3ds", this->modelMatrix, size),
				 FloorSquare(*this, "../res/3ds/floor/grass_1msq_normal_03.3ds", this->modelMatrix, size),
				 FloorSquare(*this, "../res/3ds/floor/grass_1msq_normal_04.3ds", this->modelMatrix, size),
				 FloorSquare(*this, "../res/3ds/floor/grass_1msq_normal_05.3ds", this->modelMatrix, size)})
{
	this->modelMatrix = glm::translate(this->modelMatrix, glm::vec3(0, 0, z));
	this->modelMatrix = glm::scale(this->modelMatrix, glm::vec3(size, size, size));
	std::default_random_engine e;
	std::uniform_int_distribution<unsigned> u(0, squares.size() - 1);
	for (int i = 0; i < width; i++)
	{
		std::vector<unsigned> types(static_cast<unsigned>(length));
		for (int j = 0; j < length; j++)
		{
			types[j] = u(e);
		}
		squareTypes.emplace_back(types);
	}
}

void Floor::render(const Shader &shader, const Camera &camera)
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < length; j++)
		{
			double x = i, y = j;
			squares.at(squareTypes[i][j]).renderToXY(x, y, shader, camera);
		}
	}

}

Floor::FloorSquare::FloorSquare(const Floor &parent, const std::string &filename, const glm::mat4 &up, double size)
		: Object(filename), parent(parent)
{
	material.diffuse = glm::vec3(0.5, 1, 0.5);
	material.specular = glm::vec3(0.5, 1, 0.5);
	material.ambient = glm::vec3(0.5, 1, 0.5);
}

void Floor::FloorSquare::renderToXY(double x, double y, const Shader &shader, const Camera &camera)
{
	shader.setVec3("viewPos", camera.Position);
	shader.setVec3("material.diffuse", material.diffuse);
	shader.setVec3("material.specular", material.specular);
	shader.setVec3("material.ambient", material.ambient);
	shader.setBool("usingTexture", usingTexture);
	shader.setMat4("model", glm::translate(parent.modelMatrix, glm::vec3(x, y, 0)));
	model.Draw(shader);
}
