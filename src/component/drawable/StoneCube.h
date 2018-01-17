//
// Created by ctrl on 2018/1/17.
//

#ifndef CGPROJECT_STONECUBE_H
#define CGPROJECT_STONECUBE_H

#include <TextureCube.h>
#include <TextureManager.h>
#include "Drawable.hpp"

class StoneCube: public TextureCube, public Drawable
{
public:
	explicit StoneCube(GLuint stonebrick = TextureManager::getTextureManagerInstance()->load("../res/pic/stonebrick.png"))
			: TextureCube(stonebrick, stonebrick, stonebrick, stonebrick, stonebrick, stonebrick)
	{}

	std::string getDrawableId() override {
		return "stone";
	}

};

#endif //CGPROJECT_STONECUBE_H
