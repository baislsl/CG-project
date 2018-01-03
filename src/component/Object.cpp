//
// Created by QZQ on 31/12/2017.
//

#include "Object.h"

Object::Object(const std::string &fileName) : modelFileName(fileName), model(fileName), usingTexture(true)
{}

void Object::render(const Shader &shader, const Camera &camera)
{
	shader.setVec3("viewPos", camera.Position);
	shader.setVec3("material.diffuse", material.diffuse);
	shader.setVec3("material.specular", material.specular);
	shader.setVec3("material.ambient", material.ambient);
	shader.setBool("usingTexture", usingTexture);
	shader.setMat4("model", modelMatrix);
	model.Draw(shader);
}
