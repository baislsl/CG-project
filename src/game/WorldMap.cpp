#include <drawable/Prism.hpp>
#include <drawable/TranslucenceCube.h>
#include <functional>
#include <TargetBox.hpp>
#include <drawable/WaterCube.hpp>
#include <drawable/TNTCube.hpp>
#include <JSONMapWriter.hpp>
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

	waterCube = new WaterCube();
	waterCube->modelMatrix = fitMapMatrix(waterCube->modelMatrix);
	waterCube->modelMatrix = glm::translate(waterCube->modelMatrix, glm::vec3(0, 0.01, 0));

	grassCube = new GrassCube();
	grassCube->modelMatrix = fitMapMatrix(grassCube->modelMatrix);

	TNT = new TNTCube();
	TNT->modelMatrix = fitMapMatrix(TNT->modelMatrix);

	prismMap[6] = new Prism(6, "../res/grass_square/grass.jpeg");
//	prismMap[6]->modelMatrix = glm::scale(prismMap[6]->modelMatrix, glm::vec3(size, size, size));
	prismMap[256] = new Prism(256);
//	prismMap[256]->modelMatrix = glm::scale(prismMap[256]->modelMatrix, glm::vec3(size, size, size));

	skyBox = new Skybox();
	skyBox->modelMatrix = fitMapMatrix(skyBox->modelMatrix);
	skyBox->modelMatrix = glm::scale(skyBox->modelMatrix, glm::vec3(skyBoxWidth, 40, skyBoxLength));

	translucenceCube = new TranslucenceCube();
	translucenceCube->modelMatrix = fitMapMatrix(translucenceCube->modelMatrix);
	translucenceCube->modelMatrix = glm::translate(translucenceCube->modelMatrix, glm::vec3(-1, 0, 0));

	floor = new GrassFloor(this->modelMatrix, *this, length, width, size);
	floor->modelMatrix = glm::rotate(floor->modelMatrix, glm::radians(static_cast<float >(90.0f)), glm::vec3(-1, 0, 0));

	// TODO: replace target cube
	GLuint frame = textureManager->load("../res/pic/frame.png");
	targetBox = new TargetBox(frame, frame, frame, frame, frame, frame);
	targetBox->modelMatrix = fitMapMatrix(targetBox->modelMatrix);
	targetBox->modelMatrix = glm::scale(targetBox->modelMatrix, glm::vec3(1.05, 1.05, 1.05));

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

void WorldMap::conditionRender(const Shader &shader, const Camera &camera, const std::function<bool(Component *)>& filter)
{
	auto p = camera.getCurrentPosition();
	for (auto &iter : componentMap)
	{
		if (filter(iter.first)) continue;
		for (auto &position : iter.second.positions)
		{
			if (abs((int)(p.x - position.x)) > skyBoxWidth / 2 || abs((int)(p.y - position.y)) > skyBoxLength / 2) continue;

			auto component = iter.second.component;
			auto vec = component->modelMatrix;
			component->modelMatrix = glm::translate(component->modelMatrix, position.getVector());
			component->render(shader, camera);
			component->modelMatrix = vec;
		}
	}
}

void WorldMap::render(const Shader &shader, const Camera &camera)
{
	auto p = camera.getCurrentPosition();
	floor->render(shader, camera);
	conditionRender(shader, camera, [=](Component *c)
	{
		return c == waterCube;
	});
	conditionRender(shader, camera, [=](Component *c)
	{
		return c != waterCube;
	});

	// TODO: 不知道为什么这个render放在画透明块前面会出问题
	skyBox->render(shader, camera);
	targetBox->render(shader, camera);
}

bool WorldMap::check(glm::vec3 position)
{
	auto &map = overground;
	auto x = static_cast<int>(position.x), y = static_cast<int>(position.y), z = static_cast<int>(position.z);
	if (z < 0) return true;

	auto x1 = std::floor(x), x2 = std::ceil(x);
	auto y1 = std::floor(y), y2 = std::ceil(y);
	auto z1 = std::floor(z), z2 = std::ceil(z);

	return !(map[z][x1][y1] != nullptr || map[z][x1][y2] != nullptr || map[z][x2][y1] != nullptr ||
			 map[z][x2][y2] != nullptr || map[z2][x1][y1] != nullptr || map[z2][x1][y2] != nullptr ||
			 map[z2][x2][y1] != nullptr || map[z2][x2][y2] != nullptr);
}

void WorldMap::placeblock(glm::vec3 position, int key)
{

	if (position.x >= WorldMap::width || position.x <= 0
		|| position.y >= WorldMap::length || position.y <= 0
		|| position.z >= 20 || position.z < 0)
		return;
	auto x = static_cast<int>(position.x), y = static_cast<int>(position.y), z = static_cast<int>(position.z);

	switch(key){
		case 49: fill(true, x, y, z, grassCube);break;
		case 50: fill(true, x, y, z, waterCube);break;
		case 51: fill(true, x, y, z, translucenceCube);break;
		case 52: fill(true, x, y, z, TNT);break;
		case 53: fill(true, x, y, z, prismMap[6]);break;
		case 54: fill(true, x, y, z, prismMap[256]);break;
		case 261: remove(true, x, y, z);break;
		default:;
	}
}


void WorldMap::build()
{
	fill(true, 50, 50, 0, waterCube);
	fill(true, 51, 50, 0, translucenceCube);
	fill(true, 52, 50, 0, prismMap[6]);
	fill(true, 53, 50, 0,  prismMap[256]);
	fill(true, 54, 50, 0, translucenceCube);
//	fill(true, 50, 50, 0, translucenceCube);

//	putSimpleModel(overground, 0, 50, 50, 2, translucenceCube);

	putSimpleModel(overground, 0, 50, 10, 18, prismMap[6]);
	putSimpleModel(overground, 0, 10, 50, 18, prismMap[256]);
	putSimpleModel(overground, 0, 10, 10, 18, grassCube);

	putSimpleModel(overground, 0, 30, 30, 16, grassCube);
	putSimpleModel(underground, 0, 70, 30, 16, waterCube);
	putSimpleModel(underground, 0, 30, 70, 16, waterCube);
	putSimpleModel(underground, 0, 70, 70, 16, waterCube);

	for (int i = 0; i < 8; i++)
		fill(true, 54, 54, i, prismMap[6]);

	for (int i = 0; i < 8; i++)
		fill(true, 58, 58, i, prismMap[256]);
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
	m = glm::translate(m, glm::vec3(0, 0.5, 0));
	return m;
}

bool WorldMap::hasLake(int x, int y) const
{
	return underground[0][x][y] != nullptr;
}

void WorldMap::onSave()
{
	JSONMapWriter writer(this->componentMap);
	writer.save("./data.json");
	writer.save("./data.json");
	std::cout << "save map data success!" << std::endl;
}

glm::vec3 Position::getVector()
{
	// TODO: camera y 变负值, 应该从camera视觉方向大范围改动
	return glm::vec3(x - static_cast<int>(WorldMap::width / 2), isOverground ? z : -z - 1,
					 y - static_cast<int>(WorldMap::length / 2));
}
