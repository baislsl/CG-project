#include "TextureManager.h"
#include <stb_image.h>
#include <iostream>

TextureManager *TextureManager::getTextureManagerInstance()
{
	static TextureManager* instance = new TextureManager();
	return instance;
}

GLuint TextureManager::load(const std::string &filename, int desired_channels)
{
	auto iter = textureMap.find(filename);
	if (iter != textureMap.end())
	{
		return iter->second.textureId;
	}
	GLuint texture;
	int width, height, nrChannels;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrChannels, desired_channels);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture." << std::endl;
	}
	stbi_image_free(data);
	textureMap.insert(textureMap.end(), std::pair<std::string, TextureInfo>(filename, TextureInfo(texture, width, height, nrChannels, filename)));
	return texture;
}

GLuint TextureManager::getTextureId(const std::string &path) const
{
	return textureMap.find(path)->second.textureId;
}

const TextureInfo* TextureManager::getTextureInfo(const std::string &path) const
{
	return &(textureMap.find(path)->second);
}

const TextureInfo* TextureManager::getTextureInfo(const GLuint texture) const
{
	for (auto &t : textureMap)
	{
		if(t.second.textureId == texture) return &(t.second);
	}
	return nullptr;
}

