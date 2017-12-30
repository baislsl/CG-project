#ifndef CGPROJECT_HUMAN_H
#define CGPROJECT_HUMAN_H

#include <glad/glad.h>
#include <assimp/postprocess.h>
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include "Component.h"

class Human : public Component {
public:

	Human();

	void render() override;

private:
	const aiScene *scene;
	GLuint scene_list = 0;

	void set_float4(float f[4], float a, float b, float c, float d);

	void color4_to_float4(const aiColor4D *c, float f[4]);

	void apply_material(const
						aiMaterial *mtl);

	void recursive_render(const
						  aiScene *sc, const
						  aiNode *nd);

};

#endif //CGPROJECT_HUMAN_H
