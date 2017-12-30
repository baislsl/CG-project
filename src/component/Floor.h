#ifndef CGPROJECT_FLOOR_H
#define CGPROJECT_FLOOR_H


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Component.h"

class Floor : public Component {

public:
	Floor() = default;

	void render() override;

private:
	GLfloat floor_diffuse[4] = {1.f, 0.6f, 0.6f, 1.f};
	GLfloat floor_specular[4] = {0.6f, 0.6f, 0.6f, 1.f};
	GLfloat floor_shininess = 18.f;

	GLuint floor_list = 0;
	GLuint floor_tex_id = 0;

	void tessellate_floor(float x1, float y1, float x2, float y2, int depth);

	void initTexture();

};


#endif //CGPROJECT_FLOOR_H
