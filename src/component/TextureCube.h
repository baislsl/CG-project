#ifndef CGPROJECT_TEXTURECUBE_H
#define CGPROJECT_TEXTURECUBE_H


#include "BaseShape.h"

class TextureCube : public BaseShape
{
public:
	TextureCube(GLint top, GLuint bottom, GLuint left, GLuint right, GLuint front, GLuint back);

	void render(const Shader &shader, const Camera &camera) override;

	virtual ~TextureCube() = default;

private:
	GLuint top, bottom, left, right, front, back;
};


#endif //CGPROJECT_TEXTURECUBE_H
