#ifndef CGPROJECT_WATERCUBE_HPP
#define CGPROJECT_WATERCUBE_HPP

#include <TextureCube.h>
#include <TextureManager.h>
#include "Drawable.hpp"

class WaterCube : public TextureCube, public Drawable
{
public:
	explicit WaterCube(GLuint tex = TextureManager::getTextureManagerInstance()->load("../res/pic/x.png"))
			: TextureCube(tex, tex, tex, tex, tex, tex)
	{}

	std::string getDrawableId() override {
		return "water";
	}

};

#endif //CGPROJECT_WATERCUBE_HPP
