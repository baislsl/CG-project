//
// Created by QZQ on 31/12/2017.
//

#ifndef CGPROJECT_OBJECT_H
#define CGPROJECT_OBJECT_H

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Model.h>

class Object
{
public:
	glm::mat4 modelMatrix;

	Object(const std::string &fileName) : modelFileName(fileName), model(fileName)
	{}

	void render(Shader shader)
	{
		cout << "rendering an object" << endl;
		shader.setMat4("model", modelMatrix);
		model.Draw(shader);
	}

private:
	std::string modelFileName;

	Model model;
};


#endif //CGPROJECT_OBJECT_H
