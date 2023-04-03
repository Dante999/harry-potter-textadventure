#include "hpta-lib/commands/cast.hpp"

#include "hpta-lib/persistency/persistency.hpp"
#include "hpta-lib/services/cache_service.hpp"
#include "hpta-lib/services/user_interaction_service.hpp"
#include "hpta-lib/util/hpta_strings.hpp"

#include <fmt/color.h>
#include <fmt/core.h>

#include <algorithm>
#include <variant>

bool Cast::interprete(Context &context, const std::vector<std::string> &token)
{
    // cast <spell> on <object>
    const auto screen = context.service_registry.get<User_Interaction_Service>()->get_screen();

    if (!Hpta_strings::equals_one_of(token.at(0), {"zaubere"}))
        return false;

    if (token.size() == 1) {
        screen->println("Du beherscht die folgenden Zauber:");
        screen->println("");

        for (const auto &spell_skill : context.player->get_spells()) {

            const auto &spell = context.service_registry.get<Cache_Service>()->spells->get_object(spell_skill.spell_id);

            screen->print(fmt::format(fmt::emphasis::bold, "{} (level {})\n", spell.get_name(), spell_skill.level));

            const auto lines = Hpta_strings::split_text_into_lines(
                spell.get_description(), static_cast<size_t>(screen->column_width - screen->tab_width));

            for (const auto &line : lines) {
                screen->print(fmt::format("\t{}\n", line));
            }

            screen->print("\n");
        }

        return true;
    }

    const std::string spell_id = "/spells/" + token.at(1) + ".json";

    const auto player_spells = context.player->get_spells();

    auto player_spell = std::find_if(std::begin(player_spells), std::end(player_spells),
                                     [&](const Spell_Skill &s) { return s.spell_id == spell_id; });

    if (player_spell == std::end(player_spells)) {
        screen->println("So einen Zauber kennst du nicht");
        return true;
    }

    //     try {
    //         spell = persistency::load_spell(context.gamedata_dir, "/spells/" + token.at(1) + ".json");
    //     } catch (std::runtime_error &e) {
    //         screen->println("So einen Zauber kennst du nicht");
    //         return true;
    //     }

    std::string spell_target{};

    for (size_t i = 3; i < token.size(); ++i) {
        spell_target += token.at(i);
    }

    const auto &spell = context.service_registry.get<Cache_Service>()->spells->get_object(player_spell->spell_id);
    auto &      room  = context.service_registry.get<Cache_Service>()->rooms->get_object(context.player->get_room_id());

    
    
    bool spell_applied = false;
    
    auto secrets = room.get_secrets();
    for (auto &secret : secrets) {

        if (secret.is_revealed || !secret.reveal_by_spell ||
            !Hpta_strings::equals_ignorecase(secret.name, spell_target)) {
            continue;
        }

        if (!Hpta_strings::equals_ignorecase(secret.reveal_by_spell->spell_id, spell.get_id())) {
            continue;
        }
            
        secret.is_revealed = true;
        spell_applied = true;
        
        
        for (const auto reveal_action : secret.reveal_by_spell->on_success_actions) {
            reveal_action(context);
        }


        if (!secret.reveals_item_id.empty()) {
            auto item = persistency::load_item(context.gamedata_dir, secret.reveals_item_id);
            room.add_item(Storage::Entry{1, item});
        }
        
    }
    room.set_secrets(secrets);
    
    if( !spell_applied )
    {
        screen->println("Das ergibt keine Sinn");
    }

    return true;
}
