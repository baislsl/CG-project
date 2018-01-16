#ifndef CGPROJECT_PRISM_HPP
#define CGPROJECT_PRISM_HPP


#include <common/BaseShape.h>
#include "Drawable.hpp"

// TODO: support texture for top and bottom
class Prism : public BaseShape, public Drawable
{
public:
	Prism(unsigned dimension, GLuint sideTexture);

	Prism(unsigned dimension, const std::string& path);

	explicit Prism(unsigned dimension);

	void render(const Shader &shader, const Camera &camera) override;

	std::string getDrawableId() override {
		return "prism" + std::to_string(dimension);
	}

private:
	unsigned dimension;
	GLuint sideTexture;

	void init();
};


#endif //CGPROJECT_PRISM_HPP
