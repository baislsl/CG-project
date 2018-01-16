#ifndef CGPROJECT_GRASSCUBE_HPP
#define CGPROJECT_GRASSCUBE_HPP

#include <TextureCube.h>
#include <TextureManager.h>
#include "Drawable.hpp"

class GrassCube : public TextureCube, public Drawable
{
public:
	explicit GrassCube(GLuint grassTop = TextureManager::getTextureManagerInstance()->load("../res/grass_square/grass.jpeg"),
					   GLuint grassSide = TextureManager::getTextureManagerInstance()->load("../res/grass_square/side.png"),
					   GLuint grassBottom = TextureManager::getTextureManagerInstance()->load("../res/grass_square/global.png"))
			: TextureCube(grassTop, grassBottom, grassSide, grassSide, grassSide, grassSide)
	{}

	std::string getDrawableId() override {
		return "grass";
	}

};

#endif //CGPROJECT_GRASSCUBE_HPP
