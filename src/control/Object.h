//
// Created by QZQ on 31/12/2017.
//

#ifndef CGPROJECT_OBJECT_H
#define CGPROJECT_OBJECT_H

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Model.h>
#include <Component.h>
#include <Camera.h>

class Object : public Component
{
public:
	glm::mat4 modelMatrix;
	bool usingTexture;
	explicit Object(const std::string &fileName) : modelFileName(fileName), model(fileName), usingTexture(true)
	{}

	void render(const Shader &shader, const Camera &camera) override
	{
		shader.setVec3("viewPos", camera.Position);

		//		for test
//		shader.setBool("usingTexture", false);
		shader.setVec3("material.diffuse", material.diffuse);
		shader.setVec3("material.specular", material.specular);
		shader.setVec3("material.ambient", material.ambient);
		shader.setBool("usingTexture", usingTexture);

		shader.setMat4("model", modelMatrix);
		model.Draw(shader);
	}

private:
	std::string modelFileName;

	Model model;
};


#endif //CGPROJECT_OBJECT_H
