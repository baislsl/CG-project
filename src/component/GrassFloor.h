#ifndef CGPROJECT_GRASS_H
#define CGPROJECT_GRASS_H


#include "Component.h"
#include "Plane.h"
class WorldMap;

class GrassFloor : public Component
{
public:

	GrassFloor(const glm::mat4 &up, const WorldMap& map, int length = 100, int width= 100, float size = 1.0);

	void render(const Shader& shader, const Camera& camera) override ;
private:
	int length, width;
	GLfloat size;
	glm::mat4 up;
	Plane plane;
	const WorldMap& map;
};


#endif //CGPROJECT_GRASS_H
