#include "hpta-lib/persistency/persistency.hpp"

#include "json_filehandler.hpp"

namespace persistency {
[[nodiscard]] Spell load_spell(const std::string &gamedata_dir, const std::string &id)
{
    Spell spell(id);

    Json_filehandler::load(gamedata_dir, id, [&spell](auto &d) {
        spell.set_name(d["name"].GetString());
        spell.set_description(d["description"].GetString());
    });

    return spell;
}

bool save_spell(const std::string &gamedata_dir, const Spell &spell)
{
    Json_filehandler::save(gamedata_dir, spell.get_id(), [&spell](auto &writer) {
        writer.StartObject();

        writer.Key("name");
        writer.String(spell.get_name().c_str());

        writer.Key("description");
        writer.String(spell.get_description().c_str());

        writer.EndObject();
    });

    return true;
}
} // namespace persistency
