#ifndef CGPROJECT_GAMEENTRY_H
#define CGPROJECT_GAMEENTRY_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include <getopt.h>
#include <linmath.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <assimp/matrix4x4.h>
#include <assimp/scene.h>
#include <assimp/cimport.h>
#include <GL/glu.h>
#include <assimp/postprocess.h>
#include <camera.h>
#include <iostream>
#include <cursor.h>
#include <KeyBoard.h>
#include <Input.h>
#include <Floor.h>
#include <HumanModel.h>
#include "GameManager.h"

class GameEntry {
public:
	static void run();

private:
};


#endif //CGPROJECT_GAMEENTRY_H
