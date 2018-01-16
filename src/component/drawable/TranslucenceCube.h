#ifndef CGPROJECT_TRANSLUCENCECUBE_HPP
#define CGPROJECT_TRANSLUCENCECUBE_HPP


#include <common/BaseShape.h>
#include <array>
#include "Plane.h"
#include "Drawable.hpp"


class TranslucencePlane : public BaseShape, public Drawable
{
public:
	explicit TranslucencePlane(unsigned cc = 14);

	void render(const Shader& shader, const Camera& camera) override ;

	std::string getDrawableId() override {
		return "translucence";
	}

private:
	unsigned cc;
	const static int div = 4;    // 颜色数目
	std::vector<Material> materials;
	Plane plane;
	std::vector<std::vector<int>> map;	// div表示不画

	void init();
};

class TranslucenceCube : public BaseShape
{
public:
	TranslucenceCube() = default;

	// TODO: location of this seems to exist great problem
	void render(const Shader& shader, const Camera& camera) override ;

private:
	std::array<TranslucencePlane, 6> planes;

};


#endif //CGPROJECT_TRANSLUCENCECUBE_HPP
