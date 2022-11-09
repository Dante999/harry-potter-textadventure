
#include "hpta-lib/persistency/persistency.hpp"

#include "json_filehandler.hpp"

namespace persistency {
Room load_room(const std::string &gamedata_dir, const std::string &id)
{
    Room room(id);

    Json_filehandler::load(gamedata_dir, id, [&](auto &d) {
        room.set_name(d["name"].GetString());
        room.set_description(d["description"].GetString());

        if (d.HasMember("items")) {
            for (auto &e : d["items"].GetArray()) {

                const auto item_quantity = e["quantity"].GetInt();
                const auto item_id       = e["item_id"].GetString();

                room.add_item({item_quantity, persistency::load_item(gamedata_dir, item_id)});
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

        std::vector<Npc> npcs;
        if (d.HasMember("npcs")) {
            for (auto &n : d["npcs"].GetArray()) {
                const auto npc_id = n["id"].GetString();

                npcs.emplace_back(persistency::load_npc(gamedata_dir, npc_id));
            }
        }

        room.set_npcs(npcs);
    });

    return room;
}

bool save_room(const std::string &gamedata_dir, const Room &room)
{
    Json_filehandler::save(gamedata_dir, room.get_id(), [&](auto &writer) {
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
    });

    return true;
}
} // namespace persistency
