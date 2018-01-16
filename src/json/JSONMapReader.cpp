#include "JSONMapReader.hpp"
#include <rapidjson/filereadstream.h>

using namespace rapidjson;

JSONMapReader::JSONMapReader(WorldMap &map) : worldMap(map)
{}

void JSONMapReader::read(const std::string &path)
{
	auto d = load(path);
	const Value &root = d["root"];
	assert(root.IsArray());

	for (SizeType i = 0; i < root.Size(); i++) // 使用 SizeType 而不是 size_t
	{
		const Value &ele = root[i];
		std::string id = ele["id"].GetString();
		const Value &positions = ele["positions"];
		assert(positions.IsArray());
		Component *com = worldMap.decodeComponentId(id);
		for (SizeType j = 0; j < positions.Size(); j++)
		{
			int x = positions[j]["x"].GetInt();
			int y = positions[j]["y"].GetInt();
			int z = positions[j]["z"].GetInt();
			std::string s_isOverground = positions[j]["isOverground"].GetString();
			bool isOverground = s_isOverground == "true";
			worldMap.fill(isOverground, x, y, z, com);
		}
	}


}

Document JSONMapReader::load(const std::string &path)
{
	FILE *fp = fopen(path.c_str(), "r"); // 非 Windows 平台使用 "r"
	char readBuffer[65536];
	FileReadStream is(fp, readBuffer, sizeof(readBuffer));
	Document d;
	d.ParseStream(is);
	fclose(fp);
	return d;
}
