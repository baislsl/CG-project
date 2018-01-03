#include "Cylinder.h"

Cylinder::Cylinder(int n, std::string textureFlieNameLateral, std::string textrueFileNameCircle)
{
	if (!textureFlieNameLateral.empty() && !textrueFileNameCircle.empty())
	{
		usingTexture = true;
		loadTexture(textureFlieNameLateral, textureLateral, textureWidthLateral, textureHeightLateral);
		loadTexture(textrueFileNameCircle, textureCircle, textureWidthCircle, textureHeightCircle);
	}

}

void Cylinder::loadTexture(std::string textureFileName, unsigned int &texture, int &width, int &height)
{
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	unsigned char *data = stbi_load(textureFileName.c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	} else
	{
		std::cout << "Failed to load texture." << std::endl;
	}
	stbi_image_free(data);
}
