#include <TextureManager.h>
#include "Cylinder.h"

Cylinder::Cylinder(int n, std::string textureFlieNameLateral, std::string textrueFileNameCircle)
{
	if (!textureFlieNameLateral.empty() && !textrueFileNameCircle.empty())
	{
		usingTexture = true;
		textureLateral = TextureManager::getTextureManagerInstance()->load(textureFlieNameLateral);
		textureCircle = TextureManager::getTextureManagerInstance()->load(textrueFileNameCircle);
	}

}

