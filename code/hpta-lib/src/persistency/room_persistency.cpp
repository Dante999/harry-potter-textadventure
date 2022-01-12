#include "hpta-lib/persistency/room_persistency.hpp"

#include "hpta-lib/persistency/item_persistency.hpp"

#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>
#include <rapidjson/filewritestream.h>
#include <rapidjson/prettywriter.h>

Room Room_persistency::load(const std::string &gamedata_dir, const std::string &id)
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

	Room room(id);

	room.set_name(d["name"].GetString());
	room.set_description(d["description"].GetString());

	if (d.HasMember("items")) {
		for (auto &e : d["items"].GetArray()) {

			const auto item_quantity = e["quantity"].GetInt();
			const auto item_id       = e["item_id"].GetString();

			room.add_item({item_quantity, Item_persistency::load(gamedata_dir, item_id)});
		}
	}

	std::vector<Room::Detail> details;

	if (d.HasMember("details")) {

		for (auto &e : d["details"].GetArray()) {
			const auto name        = e["name"].GetString();
			const auto description = e["description"].GetString();
			details.emplace_back(Room::Detail{name, description});
		}
	}

	room.set_details(details);

	std::vector<Room::Exit> exits;

	for (auto &e : d["exits"].GetArray()) {
		const auto direction   = e["direction"].GetString();
		const auto description = e["description"].GetString();
		const auto room_id     = e["room_id"].GetString();
		exits.emplace_back(Room::Exit{direction, description, room_id});
	}

	room.set_exits(exits);

	return room;
}

bool Room_persistency::save(const std::string &gamedata_dir, const Room &room)
{
	const std::string filepath(gamedata_dir + room.get_id());

	FILE *fp = fopen(filepath.c_str(), "wb"); // non-Windows use "r"

	if (fp == NULL) {
		throw std::runtime_error("Can open file " + filepath);
	}

	char writeBuffer[65536];

	rapidjson::FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));

	rapidjson::PrettyWriter<rapidjson::FileWriteStream> writer(os);

	writer.StartObject();

	writer.Key("name");
	writer.String(room.get_name().c_str());

	writer.Key("description");
	writer.String(room.get_description().c_str());

	writer.Key("items");
	writer.StartArray();

	for (const auto &i : room.get_items()) {
		writer.StartObject();
		writer.Key("quantity");
		writer.Int(i.quantity);

		writer.Key("item_id");
		writer.String(i.item.get_id().c_str());
		writer.EndObject();
	}

	writer.EndArray();

	writer.Key("details");
	writer.StartArray();

	for (const auto &i : room.get_details()) {
		writer.StartObject();
		writer.Key("name");
		writer.String(i.name.c_str());

		writer.Key("description");
		writer.String(i.description.c_str());
		writer.EndObject();
	}

	writer.EndArray();

	writer.Key("exits");
	writer.StartArray();

	for (const auto &e : room.get_exits()) {
		writer.StartObject();
		writer.Key("direction");
		writer.String(e.direction.c_str());

		writer.Key("description");
		writer.String(e.description.c_str());

		writer.Key("room_id");
		writer.String(e.room_id.c_str());
		writer.EndObject();
	}

	writer.EndArray();

	writer.EndObject();

	fclose(fp);

	return true;
}
