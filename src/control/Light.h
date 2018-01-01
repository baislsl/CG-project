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

	PointLight() : constant(1), linear(0.09), quadratic(0.032), position(glm::vec3(0, 0, 0)), ambient(glm::vec3(0, 0, 0)),
				   diffuse(glm::vec3(0, 0, 0)), specular(glm::vec3(0, 0, 0))
	{}
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

	void setup(const Shader &shader)
	{
//		point lights
		for (int i = 0; i < NR_POINT_LIGHTS; i++)
		{
			shader.setFloat("pointLights[" + std::string(1, i + 48) + "].constant", pointLight[i].constant);
			shader.setFloat("pointLights[" + std::string(1, i + 48) + "].linear", pointLight[i].linear);
			shader.setFloat("pointLights[" + std::string(1, i + 48) + "].quadratic", pointLight[i].quadratic);
			shader.setVec3("pointLights[" + std::string(1, i + 48) + "].position", pointLight[i].position);
			shader.setVec3("pointLights[" + std::string(1, i + 48) + "].ambient", pointLight[i].ambient);
			shader.setVec3("pointLights[" + std::string(1, i + 48) + "].diffuse", pointLight[i].diffuse);
			shader.setVec3("pointLights[" + std::string(1, i + 48) + "].specular", pointLight[i].specular);
		}
//		dirLight
		shader.setVec3("dirLight.direction", dirLight.direction);
		shader.setVec3("dirLight.ambient", dirLight.ambient);
		shader.setVec3("dirLight.diffuse", dirLight.diffuse);
		shader.setVec3("dirLight.specular", dirLight.specular);
	}

};


#endif //CGPROJECT_LIGHT_H
