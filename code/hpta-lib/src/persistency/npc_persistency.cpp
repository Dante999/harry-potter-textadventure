#include "hpta-lib/persistency/persistency.hpp"

#include "json_filehandler.hpp"

namespace persistency {
Npc load_npc(const std::string &gamedata_dir, const std::string &id)
{
    Npc npc(id);

    Json_filehandler::load(gamedata_dir, id, [&npc](auto &d) {
        npc.set_name(d["name"].GetString());
        npc.set_description(d["description"].GetString());

        std::vector<std::string> phrases;
        for (auto &phrase : d["phrases"].GetArray()) {
            phrases.emplace_back(phrase.GetString());
        }
        npc.set_phrases(phrases);
    });

    return npc;
}

bool save_npc(const std::string &gamedata_dir, const Npc &npc)
{
    Json_filehandler::save(gamedata_dir, npc.get_id(), [&npc](auto &writer) {
        writer.StartObject();

        writer.Key("name");
        writer.String(npc.get_name().c_str());

        writer.Key("description");
        writer.String(npc.get_description().c_str());

        writer.Key("phrases");
        writer.StartArray();

        for (const auto &i : npc.get_phrases()) {
            writer.String(i.c_str());
        }

        writer.EndArray();

        writer.EndObject();
    });

    return true;
}
} // namespace persistency
