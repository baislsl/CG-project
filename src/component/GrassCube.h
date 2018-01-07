#ifndef CGPROJECT_GRASSCUBE_H
#define CGPROJECT_GRASSCUBE_H


#include <Shader.h>
#include <Camera.h>
#include <stb_image.h>
#include <array>
#include "BaseShape.h"

class GrassCube : public BaseShape {
public:
	GrassCube();

	void render(const Shader &shader, const Camera &camera) override;

private:
	unsigned int texture[3];

	// TODO: 图片颜色搭配并不协调，可能需要另外换一张图片
	std::array<std::string, 3> texturePath{{
			"../res/grass_square/grass.jpeg",
			"../res/grass_square/side.png",
			"../res/grass_square/global.png"}};

	void loadTexture();
};


#endif //CGPROJECT_GRASSCUBE_H
