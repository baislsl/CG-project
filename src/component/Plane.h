//
// Created by QZQ on 03/01/2018.
//

#ifndef CGPROJECT_PLANE_H
#define CGPROJECT_PLANE_H

#include <BaseShape.h>
#include <glad/glad.h>
#include <stb_image.h>

class Plane : public BaseShape
{
public:
	explicit Plane(std::string textureFileName = std::string());
	void setTexture(std::string textureFileName);
	void useTexture(unsigned tex);
	void render(const Shader &shader, const Camera &camera) override;
	unsigned int texture;
private:
	int textureWidth{}, textureHeight{}, nrChannels{};


	void loadTexture(std::string textureFileName);
};

#endif //CGPROJECT_PLANE_H
