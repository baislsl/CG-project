#ifndef CGPROJECT_JSONMAPREADER_HPP
#define CGPROJECT_JSONMAPREADER_HPP


#include <WorldMap.hpp>
#include <rapidjson/document.h>

class JSONMapReader
{
public:
	explicit JSONMapReader(WorldMap& map);

	void read(const std::string& path);

private:
	WorldMap& worldMap;

	rapidjson::Document load(const std::string&path);
};


#endif //CGPROJECT_JSONMAPREADER_HPP
