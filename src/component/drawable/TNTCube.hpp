#ifndef CGPROJECT_TNTCUBE_HPP
#define CGPROJECT_TNTCUBE_HPP


#include <TextureCube.h>
#include <TextureManager.h>
#include "Drawable.hpp"

class TNTCube : public TextureCube, public Drawable
{
public:
	explicit TNTCube(GLuint tntTop = TextureManager::getTextureManagerInstance()->load("../res/pic/tnt_top.png"),
					 GLuint tntSide = TextureManager::getTextureManagerInstance()->load("../res/pic/tnt_side.png"),
					 GLuint tntBottom = TextureManager::getTextureManagerInstance()->load("../res/pic/tnt_bottom.png"))
			: TextureCube(tntTop, tntBottom, tntSide, tntSide, tntSide, tntSide)
	{}

	std::string getDrawableId() override {
		return "TNT";
	}

};

#endif //CGPROJECT_TNTCUBE_HPP
