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
	(void)gamedata_dir;
	(void)item;
	return true;
}
