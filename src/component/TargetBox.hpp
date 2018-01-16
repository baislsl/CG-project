#ifndef CGPROJECT_TARGETBOX_HPP
#define CGPROJECT_TARGETBOX_HPP


#include <WorldMap.hpp>
#include "TextureCube.h"

class TargetBox : public TextureCube
{
public:
	TargetBox(GLint top, GLuint bottom, GLuint left, GLuint right, GLuint front, GLuint back)
			:TextureCube(top, bottom, left, right, front, back)
	{}


	void render(const Shader& shader, const Camera& camera) override ;

private:
	Position position;


};


#endif //CGPROJECT_TARGETBOX_HPP
