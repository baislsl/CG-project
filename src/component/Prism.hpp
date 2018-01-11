#ifndef CGPROJECT_PRISM_HPP
#define CGPROJECT_PRISM_HPP


#include <common/BaseShape.h>

// TODO: support texture for top and bottom
class Prism : public BaseShape
{
public:
	Prism(unsigned dimension, GLuint sideTexture);

	Prism(unsigned dimension, const std::string& path);

	explicit Prism(unsigned dimension);

	void render(const Shader &shader, const Camera &camera) override;

private:
	unsigned dimension;
	GLuint sideTexture;

	void init();
};


#endif //CGPROJECT_PRISM_HPP
