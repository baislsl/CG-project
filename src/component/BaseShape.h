//
// Created by QZQ on 01/01/2018.
//

#ifndef CGPROJECT_BASESHAPE_H
#define CGPROJECT_BASESHAPE_H

#include <Component.h>
#include <glad/glad.h>

class BaseShape : public Component
{
public:
	unsigned int VBO, VAO;
	bool usingTexture;

	BaseShape() : usingTexture(false), VAO(0), VBO(0)
	{
		glGenBuffers(1, &VBO);
		glGenVertexArrays(1, &VAO);
	}
};


#endif //CGPROJECT_BASESHAPE_H
