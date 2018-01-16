#ifndef CGPROJECT_JSONMAP_HPP
#define CGPROJECT_JSONMAP_HPP

#include <rapidjson/document.h>

#include <vector>
#include <common/Component.h>
#include <WorldMap.hpp>

class JSONMapWriter
{
public:
	using MapType = std::vector<std::vector<std::vector<Component *>>>;

	explicit JSONMapWriter(const std::map<Component *, ComponentInfo>& map);

	bool save(const std::string& path);

	rapidjson::Document dump();


private:

	const std::map<Component *, ComponentInfo>& map;


};


#endif //CGPROJECT_JSONMAP_HPP
