#include <Prism.hpp>
#include <TranslucenceCube.h>
#include "WorldMap.hpp"

bool operator==(const Position &p1, const Position &p2)
{
	return p1.x == p2.x && p1.y == p2.y && p1.z == p2.z && p1.isOverground == p2.isOverground;
}

bool operator!=(const Position &p1, const Position &p2)
{
	return !(p1 == p2);
}

WorldMap::WorldMap(float size) : size(size), textureManager(TextureManager::getTextureManagerInstance())
{
	overground.resize(height);
	for (auto &i : overground)
	{
		i.resize(width);
		for (auto &j : i)
		{
			j.resize(length);
		}
	}
	underground.resize(height);
	for (auto &i : underground)
	{
		i.resize(width);
		for (auto &j : i)
		{
			j.resize(length);
		}
	}

	GLuint blueTexture = textureManager->load("../res/pic/x.png");
	waterCube = new TextureCube(blueTexture, blueTexture, blueTexture, blueTexture, blueTexture, blueTexture);
	waterCube->modelMatrix = fitMapMatrix(waterCube->modelMatrix);
	waterCube->modelMatrix = glm::translate(waterCube->modelMatrix, glm::vec3(0, 0.01, 0));

	GLuint grassTop = textureManager->load("../res/grass_square/grass.jpeg"), grassSide = textureManager->load(
			"../res/grass_square/side.png"), grassBottom = textureManager->load("../res/grass_square/global.png");
	grassCube = new TextureCube(grassTop, grassBottom, grassSide, grassSide, grassSide, grassSide);
	grassCube->modelMatrix = fitMapMatrix(grassCube->modelMatrix);

	prismMap[6] = new Prism(6, "../res/grass_square/grass.jpeg");
	prismMap[6]->modelMatrix = fitMapMatrix(prismMap[6]->modelMatrix);
	prismMap[80] = new Prism(80);
	prismMap[80]->modelMatrix = fitMapMatrix(prismMap[80]->modelMatrix);

	skyBox = new Skybox();
	skyBox->modelMatrix = fitMapMatrix(skyBox->modelMatrix);
	skyBox->modelMatrix = glm::scale(skyBox->modelMatrix, glm::vec3(skyBoxWidth, 40, skyBoxLength));

	translucenceCube = new TranslucenceCube();
	translucenceCube->modelMatrix = fitMapMatrix(translucenceCube->modelMatrix);

	floor = new GrassFloor(this->modelMatrix, *this, length, width, size);
	floor->modelMatrix = glm::rotate(floor->modelMatrix, glm::radians(static_cast<float >(90.0f)), glm::vec3(-1, 0, 0));
	build();
}

void WorldMap::fill(bool isOverground, int x, int y, int z, Component *component)
{
	Position position(x, y, z, isOverground);
	auto &map = isOverground ? overground : underground;
	remove(isOverground, x, y, z);
	map[z][x][y] = component;
	componentMap[component].positions.emplace_back(position);
	componentMap[component].component = component; // avoid non initialize for component
}

void WorldMap::remove(bool isOverground, int x, int y, int z)
{
	auto &map = isOverground ? overground : underground;
	Component *component = map[z][x][y];
	map[z][x][y] = nullptr;
	if (component == nullptr)
		return;
	Position position(x, y, z, isOverground);
	auto &positionList = componentMap[component].positions;
	for (auto iter = positionList.begin(); iter != positionList.end(); ++iter)
	{
		if (*iter == position)
		{
			positionList.erase(iter);
			if (positionList.empty())
				componentMap.erase(component);

			break;
		}
	}
}

void WorldMap::render(const Shader &shader, const Camera &camera)
{
	auto p = camera.getCurrentPosition();

	for (auto &iter : componentMap)
	{
		for (auto &position : iter.second.positions)
		{
			if (abs((int)(p.x - position.x)) > skyBoxWidth / 2 || abs((int)(p.y - position.y)) > skyBoxLength / 2) continue;

			auto &component = iter.second.component;
			auto vec = component->modelMatrix;
			component->modelMatrix = glm::translate(component->modelMatrix, position.getVector());
			iter.second.component->render(shader, camera);
			component->modelMatrix = vec;
		}
	}
	floor->render(shader, camera);
	skyBox->render(shader, camera);
}

bool WorldMap::check(glm::vec3 position)
{
	auto &map = overground;
	int x = position.x;
	int y = position.y;
	int z = position.z;
	if (z < 0) true;

	auto x1 = std::floor(x), x2 = std::ceil(x);
	auto y1 = std::floor(y), y2 = std::ceil(y);
	auto z1 = std::floor(z), z2 = std::ceil(z);

	return !(map[z1][x1][y1] != nullptr || map[z1][x1][y2] != nullptr || map[z1][x2][y1] != nullptr ||
			 map[z1][x2][y2] != nullptr || map[z2][x1][y1] != nullptr || map[z2][x1][y2] != nullptr ||
			 map[z2][x2][y1] != nullptr || map[z2][x2][y2] != nullptr);
}

void WorldMap::placeblock(glm::vec3 position, int key)
{

	if (position.x>=100 || position.x <=0 || position.y>=100 || position.y <=0 || position.z>=20 || position.z <=0);

	switch(key){
		case 49: fill(true,position.x,position.y,position.z,grassCube);break;
		case 50: fill(true,position.x,position.y,position.z,waterCube);break;
		case 51: fill(true,position.x,position.y,position.z,waterCube);break;
		case 52: fill(true,position.x,position.y,position.z,prismMap[6]);break;
		case 53: fill(true,position.x,position.y,position.z,prismMap[6]);break;
		case 54: fill(true,position.x,position.y,position.z,prismMap[80]);break;
	}
}


void WorldMap::build()
{
	fill(true, 50, 50, 5, waterCube);
	fill(true, 51, 50, 5, waterCube);
	fill(true, 52, 50, 5, waterCube);
	fill(true, 53, 50, 5, waterCube);
	fill(true, 54, 50, 5, waterCube);

	putSimpleModel(overground, 0, 50, 50, 2, translucenceCube);

	putSimpleModel(overground, 0, 50, 10, 18, prismMap[6]);
	putSimpleModel(overground, 0, 10, 50, 18, prismMap[80]);
	putSimpleModel(overground, 0, 10, 10, 18, grassCube);

	putSimpleModel(underground, 0, 30, 30, 16, waterCube);
	putSimpleModel(underground, 0, 70, 30, 16, waterCube);
	putSimpleModel(underground, 0, 30, 70, 16, waterCube);
	putSimpleModel(underground, 0, 70, 70, 16, waterCube);

	for (int i = 0; i < 8; i++)
		fill(true, 54, 54, i, prismMap[6]);

	for (int i = 0; i < 8; i++)
		fill(true, 58, 58, i, prismMap[80]);
}

void WorldMap::putSimpleModel(const WorldMap::MapType &map, int beginz, int centerx, int centery, int size,
							  Component *target)
{
	int z = beginz;
	bool isOverground = (map == overground);
	for (; size > 0 && z < height; size -= 2, z += 1)
	{
		for (int x = centerx - size / 2; x < centerx + size / 2; x++)
		{
			for (int y = centery - size / 2; y < centery + size / 2; y++)
			{
				fill(isOverground, x, y, z, target);
			}
		}
	}
}

WorldMap::~WorldMap()
{
	delete grassCube;
	delete waterCube;
	delete floor;
	delete skyBox;
	delete translucenceCube;
	for (auto &i : prismMap)
	{
		delete i.second;
	}
}

glm::mat4 WorldMap::fitMapMatrix(const glm::mat4 &matrix)
{
	auto m = glm::scale(matrix, glm::vec3(size, size, size));
	m = glm::translate(m, glm::vec3(0, 0.5, 1));
	return m;
}

bool WorldMap::hasLake(int x, int y) const
{
	return underground[0][x][y] != nullptr;
}

glm::vec3 Position::getVector()
{
	// TODO: camera y 变负值, 应该从camera视觉方向大范围改动
	return glm::vec3(x - static_cast<int>(WorldMap::width / 2), isOverground ? z : -z - 1,
					 y - static_cast<int>(WorldMap::length / 2));
}
