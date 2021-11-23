#include "persistency/room_persistency.hpp"

#include "persistency/item_persistency.hpp"

#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>
#include <rapidjson/filewritestream.h>
#include <rapidjson/prettywriter.h>

Direction Room_persistency::deserialize_direction(const std::string &direction)
{
	if (direction == "north")
		return Direction::NORTH;
	if (direction == "south")
		return Direction::SOUTH;
	if (direction == "east")
		return Direction::EAST;
	if (direction == "west")
		return Direction::WEST;
	if (direction == "undefined")
		return Direction::UNDEFINED;

	return Direction::UNDEFINED;
}

std::string Room_persistency::serialize_direction(const Direction direction)
{
	switch (direction) {
	case Direction::NORTH:
		return "north";
	case Direction::SOUTH:
		return "south";
	case Direction::EAST:
		return "east";
	case Direction::WEST:
		return "west";
	case Direction::UNDEFINED:
		return "undefined";
	}

	return "undefined";
}

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

	std::map<Direction, Room::Branch> exits;

	for (auto &e : d["exits"].GetArray()) {
		const auto direction   = e["direction"].GetString();
		const auto description = e["description"].GetString();
		const auto room_id     = e["room_id"].GetString();
		exits.insert({deserialize_direction(direction), {description, room_id}});
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

	writer.Key("exits");

	writer.StartArray();

	for (const auto &e : room.get_exits()) {
		writer.StartObject();
		writer.Key("direction");
		writer.String(serialize_direction(e.first).c_str());

		writer.Key("description");
		writer.String(e.second.description.c_str());

		writer.Key("room_id");
		writer.String(e.second.room_id.c_str());
		writer.EndObject();
	}

	writer.EndArray();

	writer.EndObject();

	fclose(fp);

	return true;
}
