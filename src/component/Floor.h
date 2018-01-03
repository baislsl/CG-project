#ifndef CGPROJECT_FLOOR_H
#define CGPROJECT_FLOOR_H


#include <glm/vec3.hpp>
#include "Object.h"

class Floor : public Component
{
public:
	float size;
	Floor(const glm::mat4 &up, double z, int length = 10, int width = 10, float size = 10.0);

	void render(const Shader &shader, const Camera &camera) override;

private:
	double z;
	int length, width;
	std::vector<std::vector<unsigned> > squareTypes;

	class FloorSquare : public Object
	{
	public:
		FloorSquare(const Floor& parent, const std::string &filename, const glm::mat4 &up, double size);

		void renderToXY(double x, double y, const Shader &shader, const Camera &camera);

	private:
		const Floor& parent;
	};
	std::array<FloorSquare, 5> squares;

};


#endif //CGPROJECT_FLOOR_H
