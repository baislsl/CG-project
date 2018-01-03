#include "Light.h"


PointLight::PointLight() : constant(1), linear(0.022), quadratic(0.0019), position(glm::vec3(0, 0, 0)),
						   ambient(glm::vec3(0, 0, 0)), diffuse(glm::vec3(0, 0, 0)), specular(glm::vec3(0, 0, 0))
{}

void Light::setup(const Shader &shader)
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
