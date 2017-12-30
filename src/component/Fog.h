#ifndef CGPROJECT_FOG_H
#define CGPROJECT_FOG_H


#include <glad/glad.h>
#include "Component.h"
#include <glm/vec4.hpp>

class Fog : public Component {
public:
	explicit Fog(GLfloat param = 0.05f);

	void render() override;

	GLfloat fog_color[4] = {0.1, 0.1, 0.1, 1.0};
	GLfloat param;

private:

};


#endif //CGPROJECT_FOG_H
