#include <cstring>
#include <TextureManager.h>
#include "Prism.hpp"

Prism::Prism(unsigned dimension, GLuint sideTexture) : BaseShape(true), dimension(dimension), sideTexture(sideTexture)
{ init(); }

Prism::Prism(unsigned dimension) : BaseShape(false), dimension(dimension)
{ init(); }

Prism::Prism(unsigned dimension, const std::string &path) : BaseShape(true), dimension(dimension),
		sideTexture(TextureManager::getTextureManagerInstance()->load(path))
{ init(); }

void Prism::init()
{
	// default material
	material.diffuse = glm::vec3(0.5, 0.1, 0.8);
	material.specular = glm::vec3(0.5, 0.1, 0.8);
	material.ambient = glm::vec3(0.5, 0.1, 0.8);

	float pi2 = static_cast<float>(M_PI) * 2;
	std::vector<glm::vec3> positions(dimension * 2);

	for (int i = 0; i < dimension; i++)
	{
		positions[i].z = 0;
		positions[i].x = 0.5f * sinf(i * pi2 / dimension);
		positions[i].y = 0.5f * cosf(i * pi2 / dimension);
	}

	float *vertices = new float[dimension * 8 * 3 * 4];
	size_t index = 0;

	float center[] = {0, 0, 0, 0, 0, -1, 0, 0};

	// top and buttom
	for (int i = 0; i < dimension; i++)
	{
		float buffer1[] = {positions[i].x, positions[i].y, 0, 0, 0, -1, 0, 0};
		float buffer2[] = {positions[(i + 1) % dimension].x, positions[(i + 1) % dimension].y, 0, 0, 0, -1, 0, 0};
		memcpy(vertices + index + i * 8 * 3, buffer1, sizeof(buffer1));
		memcpy(vertices + index + i * 8 * 3  + 8, buffer2, sizeof(buffer2));
		memcpy(vertices + index + i * 8 * 3 + 16, center, sizeof(center));
	}
	index += dimension * 8 * 3;
	center[2] = 1;
	center[5] = 1;
	for (int i = 0; i < dimension; i++)
	{
		float buffer1[] = {positions[i].x, positions[i].y, 1, 0, 0, 1, 0, 0};
		float buffer2[] = {positions[(i + 1) % dimension].x, positions[(i + 1) % dimension].y, 1, 0, 0, 1, 0, 0};
		memcpy(vertices + index + i * 8 * 3, buffer1, sizeof(buffer1));
		memcpy(vertices + index + i * 8 * 3  + 8, buffer2, sizeof(buffer2));
		memcpy(vertices + index + i * 8 * 3 + 16, center, sizeof(center));
	}
	index += dimension * 8 * 3;

	// sides
	for (int i = 0; i < dimension; i++)
	{
		float buffer[3][8] = {
				{positions[i].x, positions[i].y, 0, sinf((0.5f + i) * pi2/dimension), cosf((0.5f + i)* pi2/dimension), 0, 0, 0},
				{positions[(i + 1) % dimension].x, positions[(i + 1) % dimension].y, 0, sinf((0.5f + i)* pi2/dimension),  cosf((0.5f + i)* pi2/dimension), 0, 0, 1},
				{positions[(i + 1) % dimension].x, positions[(i + 1) % dimension].y, 1, sinf((0.5f + i)* pi2/dimension),  cosf((0.5f + i)* pi2/dimension), 0, 1, 0},
		};
		memcpy(vertices + index + i * 3 * 8, buffer, sizeof(buffer));
	}
	index += dimension * 8 * 3;
	for (int i = 0; i < dimension; i++)
	{
		float buffer[3][8] = {
				{positions[(i - 1 + dimension) % dimension].x, positions[(i - 1 + dimension) % dimension].y, 0, sinf((-0.5f + i)* pi2/dimension), cosf((-0.5f + i)* pi2/dimension), 0, 0, 1},
				{positions[(i - 1 + dimension) % dimension].x, positions[(i - 1 + dimension) % dimension].y, 1, sinf((-0.5f + i)* pi2/dimension),  cosf((-0.5f + i)* pi2/dimension), 0, 1, 0},
				{positions[i].x, positions[i].y, 1, sinf((-0.5f + i)* pi2/dimension),  cosf((-0.5f + i)* pi2/dimension), 0, 1, 1},
		};
		memcpy(vertices + index + i * 3 * 8, buffer, sizeof(buffer));
	}
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, dimension * 8 * 3 * 4 * sizeof(float), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	delete[] vertices;
}

void Prism::render(const Shader &shader, const Camera &camera)
{
	shader.setMat4("model", modelMatrix);
	shader.setVec3("viewPos", camera.Position);
	shader.setVec3("material.diffuse", material.diffuse);
	shader.setVec3("material.specular", material.specular);
	shader.setVec3("material.ambient", material.ambient);
	shader.setBool("usingTexture", usingTexture);
	shader.setFloat("material.shininess", material.shininess);
	if (usingTexture) glBindTexture(GL_TEXTURE_2D, sideTexture);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 4 * 3 * dimension);
}
