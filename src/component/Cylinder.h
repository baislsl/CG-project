//
// Created by QZQ on 01/01/2018.
//

#ifndef CGPROJECT_CYLINDER_H
#define CGPROJECT_CYLINDER_H

#include <BaseShape.h>
#include <glad/glad.h>
#include <stb_image.h>
#include <cmath>

class Cylinder : public BaseShape
{
public:
	explicit Cylinder(int n = 20, std::string textureFlieNameLateral = std::string(), std::string textrueFileNameCircle = std::string());

private:
	int textureWidthLateral, textureHeightLateral, nrChannels, textureWidthCircle, textureHeightCircle;
	unsigned int textureLateral, textureCircle;

	void loadTexture(std::string textureFileName, unsigned int &texture, int &width, int &height);
};

#endif //CGPROJECT_CYLINDER_H
