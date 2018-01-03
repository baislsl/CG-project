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

	void render(const Shader &shader, const Camera &camera) override;

private:
	int textureWidth, textureHeight, nrChannels;
	unsigned int texture;

	void loadTexture(std::string textureFileName);
};

#endif //CGPROJECT_CUBE_H
