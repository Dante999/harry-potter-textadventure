
#include "hpta-lib/persistency/persistency.hpp"

#include "json_filehandler.hpp"

namespace {
std::vector<Action> get_actions(const std::string &node_name, const rapidjson::Value &parent_node)
{
    std::vector<Action> actions;

    if (parent_node.HasMember(node_name.c_str())) {
        for (auto &sucess_action : parent_node[node_name.c_str()].GetArray()) {

            const std::string action_name  = sucess_action["name"].GetString();
            const auto &      action_value = sucess_action["value"];

            if (action_value.IsString()) {
                const auto action = create_action(action_name, std::string{action_value.GetString()});

                if (action) {
                    actions.emplace_back(*action);
                }
            }
        }
    }
    return actions;
}
} // namespace

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
                
                secret.description_on_reveal =
                    get_str_or_empty(s, "description_on_reveal"); // will be replaced with action
                secret.needs_item_id   = get_str_or_empty(s, "needs_item");
                secret.needs_password  = get_str_or_empty(s, "needs_password");
                secret.needs_spell_id  = get_str_or_empty(s, "needs_spell");
                secret.reveals_item_id = get_str_or_empty(s, "reveals_item");

                if (s.HasMember("reveal_by_spell")) {
                    auto &rbs = s["reveal_by_spell"];

                    secret.reveal_by_spell = Room::Reveal_By_Spell{};

                    secret.reveal_by_spell->spell_id   = rbs["spell_id"].GetString();
                    secret.reveal_by_spell->difficulty = rbs["difficulty"].GetInt();

                    secret.reveal_by_spell->on_success_actions      = get_actions("on_success_actions", rbs);
                    secret.reveal_by_spell->on_crit_success_actions = get_actions("on_crit_success_actions", rbs);
                    secret.reveal_by_spell->on_failure_actions      = get_actions("on_failure_actions", rbs);
                    secret.reveal_by_spell->on_crit_failure_actions = get_actions("on_crit_failure_actions", rbs);
                }
                else {
                    secret.reveal_by_spell = std::nullopt;
                }

                if (s.HasMember("reveal_by_item")) {
                    auto &rbi = s["reveal_by_item"];

                    secret.reveal_by_item = Room::Reveal_By_Item{};

                    secret.reveal_by_item->item_id             = rbi["item_id"].GetString();
                    secret.reveal_by_item->item_gets_destroyed = rbi["item_gets_destroyed"].GetBool();

                    secret.reveal_by_item->on_success_actions = get_actions("on_success_actions", rbi);
                }
                else {
                    secret.reveal_by_item = std::nullopt;
                }

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
