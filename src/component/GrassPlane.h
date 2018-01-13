#ifndef CGPROJECT_FLOOR_H
#define CGPROJECT_FLOOR_H


#include <glm/vec3.hpp>
#include <array>
#include "Object.h"

class WorldMap;
class GrassPlane : public Component
{
public:
	float size;
	GrassPlane(const glm::mat4 &up, const WorldMap& map, double z, int length = 10, int width = 10, float size = 10.0);

	void render(const Shader &shader, const Camera &camera) override;

private:
	double z;
	int length, width;
	std::vector<std::vector<unsigned> > squareTypes;
	const WorldMap& map;

	class GrassSquare : public Object
	{
	public:
		GrassSquare(const GrassPlane& parent, const std::string &filename, const glm::mat4 &up, double size);

		void renderToXY(double x, double y, const Shader &shader, const Camera &camera);

	private:
		const GrassPlane& parent;
	};
	std::array<GrassSquare, 5> squares;


};


#endif //CGPROJECT_FLOOR_H
