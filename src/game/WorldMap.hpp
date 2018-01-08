#ifndef CGPROJECT_WORLDMAP_HPP
#define CGPROJECT_WORLDMAP_HPP

#include <vector>
#include <Component.h>
#include <map>
#include <TextureManager.h>
#include <GrassCube.h>
#include <Grass.h>

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
 */

class ComponentInfo;
class Position;

class WorldMap : public Component
{
public:
	static const size_t width = 100, length = 100, height = 20;
	float size;

	explicit WorldMap(float size = 1.0);

	virtual void fill(bool isOverground, int x, int y, int z, Component *component);

	virtual void remove(bool isOverground, int x, int y, int z);

	virtual ~WorldMap();

	void render(const Shader &shader, const Camera &camera) override;

private:

	using MapType = std::vector<std::vector<std::vector<Component *>>>;

	MapType overground;
	MapType underground;
	std::map<Component *, ComponentInfo> componentMap;
	TextureManager *textureManager;
	TextureCube *grassCube, *waterCube;
	Grass* floor;

	void build();

	// 简单的搭建造一个塔形
	void putSimpleModel(const MapType &map, int beginz, int centerx, int centery, int size, Component *target);

};

struct Position
{
	int x, y, z;
	bool isOverground;

	Position() = default;

	Position(int x, int y, int z, bool isOverground) : x(x), y(y), z(z), isOverground(isOverground)
	{};

	glm::vec3 getVector()
	{
		return glm::vec3(x, y, isOverground ? z : -z - 1);
	}
};

struct ComponentInfo
{
	Component *component;
	std::vector<Position> positions;

	explicit ComponentInfo(Component *component = nullptr) : component(component), positions()
	{}

};

#endif //CGPROJECT_WORLDMAP_HPP
