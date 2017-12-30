#include "Fog.h"

void Fog::render() {
	glFogi(GL_FOG_MODE, GL_EXP);
	glFogf(GL_FOG_DENSITY, 0.05f);
	glFogfv(GL_FOG_COLOR, fog_color);
}

Fog::Fog(GLfloat param) : param(param) {}
