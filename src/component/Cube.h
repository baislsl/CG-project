//
// Created by QZQ on 01/01/2018.
//

#ifndef CGPROJECT_CUBE_H
#define CGPROJECT_CUBE_H

#include <BaseShape.h>
#include <glad/glad.h>
#include <stb_image.h>

class Cube : public BaseShape
{
public:
	explicit Cube(std::string textureFileName = std::string());

	explicit Cube(GLuint texture);

	void render(const Shader &shader, const Camera &camera) override;

private:
	unsigned int texture;

	void init();
};

#endif //CGPROJECT_CUBE_H
