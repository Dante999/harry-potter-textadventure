#include "hpta-lib/persistency/item_persistency.hpp"

#include "hpta-lib/persistency/json_filehandler.hpp"

Item Item_persistency::load(const std::string &gamedata_dir, const std::string &id)
{
	Item item(id);

	Json_filehandler::load(gamedata_dir, id, [&item](auto &d) {
		item.set_name(d["name"].GetString());
		item.set_description(d["description"].GetString());
	});

	return item;
}

bool Item_persistency::save(const std::string &gamedata_dir, const Item &item)
{
	Json_filehandler::save(gamedata_dir, item.get_id(), [&item](auto &writer) {
		writer.StartObject();

		writer.Key("name");
		writer.String(item.get_name().c_str());

		writer.Key("description");
		writer.String(item.get_description().c_str());

		writer.EndObject();
	});

	return true;
}
