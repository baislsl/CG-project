#ifndef CGPROJECT_COMPONENT_H
#define CGPROJECT_COMPONENT_H
#include <Shader.h>
#include <Camera.h>

class Material
{
public:
	glm::vec3 ambient, diffuse, specular;
	Material():ambient(glm::vec3(0,0,0)), diffuse(glm::vec3(0,0,0)), specular(glm::vec3(0,0,0))
	{}
};

class Component {
public:
	Material material;

	virtual void render(const Shader &shader, const Camera &camera) = 0;

	virtual ~Component() = default;

};

#endif //CGPROJECT_COMPONENT_H
