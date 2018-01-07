#ifndef CGPROJECT_TEXTUREMANAGER_H
#define CGPROJECT_TEXTUREMANAGER_H

#include <string>
#include <glad/glad.h>
#include <map>


struct TextureInfo
{
	GLuint textureId;
	int width, height, nrChannels;
	std::string path;


	TextureInfo() = default;

	TextureInfo(GLuint textureId, int width, int height, int nrChannels, const std::string &path) : textureId(textureId), width(width),
			height(height), nrChannels(nrChannels), path(path)
	{}
};

class TextureManager
{
public:
	static TextureManager *getTextureManagerInstance();

	GLuint load(const std::string &filename, int desired_channels = 0);

	GLuint getTextureId(const std::string &path) const;

	const TextureInfo* getTextureInfo(const std::string &path) const;

	const TextureInfo* getTextureInfo(const GLuint texture) const
	{
		for (auto &t : textureMap)
		{
			if(t.second.textureId == texture) return &(t.second);
		}
		return nullptr;
	}


private:
	TextureManager() = default;

	std::map<std::string, TextureInfo> textureMap;
};


#endif //CGPROJECT_TEXTUREMANAGER_H
