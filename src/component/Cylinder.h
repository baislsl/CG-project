//
// Created by QZQ on 01/01/2018.
//

#ifndef CGPROJECT_CYLINDER_H
#define CGPROJECT_CYLINDER_H

#include <BaseShape.h>
#include <glad/glad.h>
#include <stb_image.h>
#include <cmath>

class Cylinder : public BaseShape
{
public:
	explicit Cylinder(int n = 20, std::string textureFlieNameLateral = std::string(), std::string textrueFileNameCircle = std::string());

private:
	unsigned int textureLateral, textureCircle;

};

#endif //CGPROJECT_CYLINDER_H
