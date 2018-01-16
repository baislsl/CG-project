#include <Shader.h>
#include <Camera.h>
#include "TextureCube.h"
#include "Skybox.h"

void Skybox::render(const Shader &shader, const Camera &camera)
{
	shader.setMat4("view",  glm::mat4(glm::mat3(camera.GetViewMatrix())));
	shader.setMat4("model", modelMatrix);
	shader.setVec3("material.diffuse", material.diffuse);
	shader.setVec3("material.specular", material.specular);
	shader.setVec3("material.ambient", material.ambient);
	shader.setFloat("material.shininess", material.shininess);
	shader.setBool("usingTexture", usingTexture);

	glBindVertexArray(VAO);
	glBindTexture(GL_TEXTURE_2D, top);    // top
	glDrawArrays(GL_TRIANGLES, 30, 6);

	// TODO: left, right, front, back 顺序没有搞好
	glBindTexture(GL_TEXTURE_2D, left);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindTexture(GL_TEXTURE_2D, right);
	glDrawArrays(GL_TRIANGLES, 6, 6);

	glBindTexture(GL_TEXTURE_2D, back);
	glDrawArrays(GL_TRIANGLES, 12, 6);

	glBindTexture(GL_TEXTURE_2D, front);
	glDrawArrays(GL_TRIANGLES, 18, 6);

	glBindTexture(GL_TEXTURE_2D, bottom);    // bottom
	glDrawArrays(GL_TRIANGLES, 24, 6);
}
