#ifndef CGPROJECT_OBJECT_H
#define CGPROJECT_OBJECT_H

#include <Model.h>
#include "Component.h"
#include "Camera.h"

class Object : public Component
{
public:

	bool usingTexture;
	explicit Object(const std::string &fileName);

	void render(const Shader &shader, const Camera &camera) override;

protected:
	std::string modelFileName;

	Model model;
};


#endif //CGPROJECT_OBJECT_H
