#include "TargetBox.hpp"

void TargetBox::render(const Shader &shader, const Camera &camera)
{
	Position pos(camera.nextPlacePosition()-camera.transPosition(camera.Position)+glm::vec3(50,50,0));
//	std::cout << "pos: x=" << pos.x << ",y=" << pos.y << ",z=" << pos.z << std::endl;

	glm::mat4 vec = modelMatrix;
	modelMatrix = glm::translate(modelMatrix, pos.getVector());
	TextureCube::render(shader, camera);
	modelMatrix = vec;

}
