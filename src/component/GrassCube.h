#ifndef CGPROJECT_GRASSCUBE_H
#define CGPROJECT_GRASSCUBE_H


#include <Shader.h>
#include <Camera.h>
#include <array>
#include <TextureManager.h>
#include "TextureCube.h"

class GrassCube : public TextureCube {
public:
	explicit GrassCube(GLuint top = TextureManager::getTextureManagerInstance()->load("../res/grass_square/grass.jpeg"),
			  GLuint side = TextureManager::getTextureManagerInstance()->load("grass_square/side.png"),
			  GLuint bottom = TextureManager::getTextureManagerInstance()->load("../res/grass_square/global.png")) :
	TextureCube(top, bottom, side, side, side, side){}
private:
	// TODO: 图片颜色搭配并不协调，可能需要另外换一张图片
};


#endif //CGPROJECT_GRASSCUBE_H
