//
// Created by QZQ on 31/12/2017.
//

#ifndef CGPROJECT_MODEL_H
#define CGPROJECT_MODEL_H

#include <glad/glad.h>
#include <Mesh.h>
#include <Shader.h>
#include <vector>
#include <string>
#include <assimp/scene.h>

//unsigned int TextureFromFile(const char *path, const string &directory, bool gamma = false);

class Model 
{
public:
    /*  Model Data */
    std::vector<Texture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
    std::vector<Mesh> meshes;
    std::string directory;
    bool gammaCorrection;

    /*  Functions   */
    // constructor, expects a filepath to a 3D model.
	explicit Model(std::string const &path, bool gamma = false);

    // draws the model, and thus all its meshes
    void Draw(Shader shader);
    
private:
    /*  Functions   */
    // loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
    void loadModel(std::string const &path);

    // processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
    void processNode(aiNode *node, const aiScene *scene);

    Mesh processMesh(aiMesh *mesh, const aiScene *scene);

    // checks all material textures of a given type and loads the textures if they're not loaded yet.
    // the required info is returned as a Texture struct.
    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);

    unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);
};


#endif


