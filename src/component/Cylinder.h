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
	explicit Cylinder(int n = 20, std::string textureFlieNameLateral = std::string(), std::string textrueFileNameCircle = std::string())
	{
		if (!textureFlieNameLateral.empty() && !textrueFileNameCircle.empty())
		{
			usingTexture = true;
			loadTexture(textureFlieNameLateral, textureLateral, textureWidthLateral, textureHeightLateral);
			loadTexture(textrueFileNameCircle, textureCircle, textureWidthCircle, textureHeightCircle);
		}

	}

private:
	int textureWidthLateral, textureHeightLateral, nrChannels, textureWidthCircle, textureHeightCircle;
	unsigned int textureLateral, textureCircle;

	void loadTexture(std::string textureFileName, unsigned int &texture, int &width, int &height)
	{
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		unsigned char *data = stbi_load(textureFileName.c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load texture." << std::endl;
		}
		stbi_image_free(data);
	}
};

#endif //CGPROJECT_CYLINDER_H
