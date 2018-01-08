//
// Created by QZQ on 01/01/2018.
//

#ifndef CGPROJECT_LIGHT_H
#define CGPROJECT_LIGHT_H

#include <glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Shader.h>
#include <string>
#include <cstdlib>

#define NR_POINT_LIGHTS 4

class PointLight
{
public:
	glm::vec3 position, ambient, diffuse, specular;

	float constant, linear, quadratic;
	bool use;
	PointLight();
};

class DirLight
{
public:
	glm::vec3 direction, ambient, diffuse, specular;
};

class Light
{
public:
	PointLight pointLight[NR_POINT_LIGHTS];
	DirLight dirLight;

	void setup(const Shader &shader);

};


#endif //CGPROJECT_LIGHT_H
