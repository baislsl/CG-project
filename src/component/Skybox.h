#ifndef CGPROJECT_SKYBOX_H
#define CGPROJECT_SKYBOX_H

#include <Shader.h>
#include <Camera.h>
#include <array>
#include <TextureManager.h>
#include "TextureCube.h"


class Skybox : public TextureCube {
public:
    explicit Skybox(GLuint top = TextureManager::getTextureManagerInstance()->load("../res/skybox/siege_top.jpg"),
                    GLuint left = TextureManager::getTextureManagerInstance()->load("../res/skybox/siege_left.jpg"),
                    GLuint right = TextureManager::getTextureManagerInstance()->load("../res/skybox/siege_right.jpg"),
                    GLuint front = TextureManager::getTextureManagerInstance()->load("../res/skybox/siege_front.jpg"),
                    GLuint back = TextureManager::getTextureManagerInstance()->load("../res/skybox/siege_back.jpg")
    ):
            TextureCube(top, 0, left, right, front, back){}

	void render(const Shader& shader, const Camera& camera) override ;

private:

};



#endif //CGPROJECT_SKYBOX_H
