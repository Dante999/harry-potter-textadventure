#include "hpta-lib/persistency/item_persistency.hpp"

#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>
#include <rapidjson/filewritestream.h>
#include <rapidjson/prettywriter.h>

Item Item_persistency::load(const std::string &gamedata_dir, const std::string &id)
{
	const std::string filepath(gamedata_dir + id);

	FILE *fp = fopen(filepath.c_str(), "rb"); // non-Windows use "r"

	if (fp == NULL) {
		throw std::runtime_error("Can not find file " + filepath);
	}

	char readBuffer[65536];

	rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));

	rapidjson::Document d;
	d.ParseStream(is);

	fclose(fp);

	Item item(id);

	item.set_name(d["name"].GetString());
	item.set_description(d["description"].GetString());

	return item;
}

bool Item_persistency::save(const std::string &gamedata_dir, const Item &item)
{
	const std::string filepath(gamedata_dir + item.get_id());

	FILE *fp = fopen(filepath.c_str(), "wb"); // non-Windows use "r"

	if (fp == NULL) {
		throw std::runtime_error("Can open file " + filepath);
	}

	char writeBuffer[65536];

	rapidjson::FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));

	rapidjson::PrettyWriter<rapidjson::FileWriteStream> writer(os);

	writer.StartObject();

	writer.Key("name");
	writer.String(item.get_name().c_str());

	writer.Key("description");
	writer.String(item.get_description().c_str());

	writer.EndObject();

	fclose(fp);

	return true;
}
