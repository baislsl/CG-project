#ifndef CGPROJECT_GRASS_H
#define CGPROJECT_GRASS_H


#include "Component.h"
#include "Plane.h"

class Grass : public Component
{
public:

	explicit Grass(const glm::mat4 &up, int length = 40, int width= 40, float size = 3.0);

	void render(const Shader& shader, const Camera& camera) override ;
private:
	int length, width;
	GLfloat size;
	glm::mat4 up;
	Plane plane;
};


#endif //CGPROJECT_GRASS_H
