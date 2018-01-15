#include <TextureManager.h>
#include "Plane.h"


Plane::Plane(GLuint texture) : texture(texture)
{ init(); }

Plane::Plane(std::string textureFileName)
{
	if (!textureFileName.empty())
	{
		usingTexture = true;
		texture = TextureManager::getTextureManagerInstance()->load(textureFileName);
	}
	init();
}

void Plane::render(const Shader &shader, const Camera &camera)
{
	shader.setMat4("model", modelMatrix);
	shader.setVec3("viewPos", camera.Position);
	shader.setVec3("material.diffuse", material.diffuse);
	shader.setVec3("material.specular", material.specular);
	shader.setVec3("material.ambient", material.ambient);
	shader.setFloat("material.shininess", material.shininess);
	shader.setBool("usingTexture", usingTexture);
	if (usingTexture) glBindTexture(GL_TEXTURE_2D, texture);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Plane::setTexture(std::string textureFileName)
{
	usingTexture = true;
	this->texture = TextureManager::getTextureManagerInstance()->load(textureFileName);
}

void Plane::useTexture(unsigned tex)
{
	usingTexture = true;
	texture = tex;
}

void Plane::init()
{
	// TODO: consider 改边长为1
	float vertices[] = {-1, -1, 0, 0, 0, 1, 0, 0, -1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, -1, -1, 0, 0, 0, 1,
						0, 0, 1, -1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1,};
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (6 * sizeof(float)));
	glEnableVertexAttribArray(2);
}
