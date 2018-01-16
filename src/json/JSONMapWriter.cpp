#include "JSONMapWriter.hpp"
#include <rapidjson/writer.h>
#include <rapidjson/filewritestream.h>

using namespace rapidjson;

JSONMapWriter::JSONMapWriter(const std::map<Component *, ComponentInfo> &map) : map(map)
{}


bool JSONMapWriter::save(const std::string &path)
{
	auto d = dump();
	FILE *fp = fopen(path.c_str(), "w"); // 非 Windows 平台使用 "w"
	char writeBuffer[65536];
	FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));
	Writer<FileWriteStream> writer(os);
	d.Accept(writer);
	fclose(fp);
}

rapidjson::Document JSONMapWriter::dump()
{
	Document d;
	d.SetObject();

	Value root(kArrayType);
	{
		for (auto m : map)
		{
			Component *c = m.first;
			const ComponentInfo &info = m.second;
			Value ele(kObjectType);
			{
				Value id;
				const std::string s = dynamic_cast<Drawable *>(c)->getDrawableId();
				id.SetString(s.c_str(), s.length(), d.GetAllocator());
				ele.AddMember("id", id, d.GetAllocator());
				Value poss(kArrayType);
				for (auto &pos : info.positions)
				{
					Value p(kObjectType);
					{
						Value x(pos.x); p.AddMember("x", x, d.GetAllocator());
						Value y(pos.y); p.AddMember("y", y, d.GetAllocator());
						Value z(pos.z); p.AddMember("z", z, d.GetAllocator());
						std::string si = pos.isOverground ? "true" : "false";
						Value isOverground(si.c_str(), si.length(), d.GetAllocator());
						p.AddMember("isOverground", isOverground, d.GetAllocator());
					}
					poss.PushBack(p, d.GetAllocator());
				}
				ele.AddMember("positions", poss, d.GetAllocator());
			}
			root.PushBack(ele, d.GetAllocator());
		}
	}
	d.SetObject().AddMember("root", root, d.GetAllocator());

	return d;

}
