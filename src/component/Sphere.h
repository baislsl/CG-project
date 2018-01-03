//
// Created by QZQ on 01/01/2018.
//

#ifndef CGPROJECT_SPHERE_H
#define CGPROJECT_SPHERE_H

#include <BaseShape.h>
#include <glad/glad.h>
#include <stb_image.h>
#include <cmath>

class Sphere : public BaseShape
{
public:
	int nrVert;
	unsigned int EBO;

//	m and n are number of slices vertically and horizontally
	explicit Sphere(int m = 10, int n = 10, std::string textureFileName = std::string());

	void render(const Shader &shader, const Camera &camera) override;

private:
	int textureWidth, textureHeight, nrChannels;
	unsigned int texture;

	void loadTexture(std::string textureFileName);
};

#endif //CGPROJECT_SPHERE_H
