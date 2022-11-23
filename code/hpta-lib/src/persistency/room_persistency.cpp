
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

        std::vector<Room::Secret> secrets;
        if (d.HasMember("secrets")) {
            for (auto &s : d["secrets"].GetArray()) {

                const auto get_str_or_empty = [&](auto &node, const std::string &key) {
                    return node.HasMember(key.c_str()) ? node[key.c_str()].GetString() : "";
                };

                Room::Secret secret;
                secret.is_revealed               = false;
                secret.name                      = s["name"].GetString();
                secret.description_before_reveal = s["description_before_reveal"].GetString();
                secret.description_after_reveal  = s["description_after_reveal"].GetString();
                secret.description_on_reveal            = s["description_on_reveal"].GetString();
                secret.needs_item_id             = get_str_or_empty(s, "needs_item");
                secret.needs_password            = get_str_or_empty(s, "needs_password");
                secret.needs_spell_id            = get_str_or_empty(s, "needs_spell");
                secret.reveals_item_id           = get_str_or_empty(s, "reveals_item");

                secrets.emplace_back(secret);
            }
        }

        room.set_secrets(secrets);
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

        writer.Key("secrets");
        writer.StartArray();

        for (const auto &secret : room.get_secrets()) {
            writer.StartObject();

            writer.Key("name");
            writer.String(secret.name.c_str());

            writer.Key("description_before_reveal");
            writer.String(secret.description_before_reveal.c_str());

            writer.Key("description_on_reveal");
            writer.String(secret.description_on_reveal.c_str());

            writer.Key("description_after_reveal");
            writer.String(secret.description_after_reveal.c_str());

            if (!secret.needs_item_id.empty()) {
                writer.Key("needs_item");
                writer.String(secret.needs_item_id.c_str());
            }

            if (!secret.needs_password.empty()) {
                writer.Key("needs_password");
                writer.String(secret.needs_password.c_str());
            }

            if (!secret.needs_spell_id.empty()) {
                writer.Key("needs_spell");
                writer.String(secret.needs_spell_id.c_str());
            }

            if (!secret.reveals_item_id.empty()) {
                writer.Key("reveals_item");
                writer.String(secret.reveals_item_id.c_str());
            }

            writer.EndObject();
        }

        writer.EndArray();

        writer.EndObject();
    });

    return true;
}
} // namespace persistency
