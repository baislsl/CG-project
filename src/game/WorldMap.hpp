#ifndef CGPROJECT_WORLDMAP_HPP
#define CGPROJECT_WORLDMAP_HPP

#include <vector>
#include <Component.h>
#include <map>
#include <TextureManager.h>
#include <GrassCube.h>
#include <Skybox.h>
#include <GrassFloor.h>
#include "Prism.hpp"

/**
 *   z, x, y
 *   z < 0 地下
 *  维护两个数据结构以加快图形绘制速度
 *  	1. 所有能render的图形，逐个绘制
 *  	2. 地图，就是某个位置能不能进入去，实现简单的实现碰撞检测
 *
 *
 *  一定要保持两者的一致，防止出现视图和操作碰撞不同的情况
 *
 *  注意地底和地上的连接通道, 该通道为underground[0][x][y]
 *	(z, x, y)
 *
 *	z [0, height)
 *	x [0, width)
 *	y [0, length)
 *
 *	中心点(width/2, length/2), 为了避免不必要的麻烦，请保证width和height为偶数
 */

class ComponentInfo;

class Position;

class WorldMap : public Component
{
public:
	static const size_t width = 100, length = 100, height = 20;
	float size;

	explicit WorldMap(float size = 1.0);

	void fill(bool isOverground, int x, int y, int z, Component *component);

	void remove(bool isOverground, int x, int y, int z);

	bool hasLake(int x, int y) const;

	~WorldMap() override ;

	void render(const Shader &shader, const Camera &camera) override;

	int check(float x, float y, float z);

private:

	using MapType = std::vector<std::vector<std::vector<Component *>>>;

	MapType overground;
	MapType underground;
	std::map<Component *, ComponentInfo> componentMap;
	TextureManager *textureManager;
	TextureCube *grassCube, *waterCube, *skyBox;
	std::map<unsigned , Prism*> prismMap;
	GrassFloor* floor;

	void build();

	// 简单的搭建造一个塔形
	void putSimpleModel(const MapType &map, int beginz, int centerx, int centery, int size, Component *target);

	glm::mat4 fitMapMatrix(const glm::mat4 &matrix);

};

struct Position
{
	int x, y, z;
	bool isOverground;

	Position() = default;

	Position(int x, int y, int z, bool isOverground) : x(x), y(y), z(z), isOverground(isOverground)
	{};

	glm::vec3 getVector();
};

struct ComponentInfo
{
	Component *component;
	std::vector<Position> positions;

	explicit ComponentInfo(Component *component = nullptr) : component(component), positions()
	{}

};

#endif //CGPROJECT_WORLDMAP_HPP
