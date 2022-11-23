#include "hpta-lib/commands/cast.hpp"

#include "hpta-lib/persistency/persistency.hpp"
#include "hpta-lib/services/room_cache_service.hpp"
#include "hpta-lib/services/user_interaction_service.hpp"
#include "hpta-lib/util/hpta_strings.hpp"

#include <fmt/core.h>

bool Cast::interprete(Context &context, const std::vector<std::string> &token)
{
    // cast <spell> on <object>
    const auto screen = context.service_registry.get<User_Interaction_Service>()->get_screen();

    if (!Hpta_strings::equals_one_of(token.at(0), {"zaubere"}))
        return false;

    Spell spell{"undefined"};
    try {
        spell = persistency::load_spell(context.gamedata_dir, "/spells/" + token.at(1) + ".json");
    } catch (std::runtime_error &e) {
        screen->println("So einen Zauber kennst du nicht");
        return true;
    }

    std::string spell_target{};

    for (size_t i = 3; i < token.size(); ++i) {
        spell_target += token.at(i);
    }

    auto &room = context.service_registry.get<Room_cache_service>()->get_room(context.player->get_room_id());

    auto secrets = room.get_secrets();
    for (auto &secret : secrets) {
        if (Hpta_strings::equals_ignorecase(secret.name, spell_target) && !secret.is_revealed &&
            Hpta_strings::equals_ignorecase(secret.needs_spell_id, spell.get_id())) {
            secret.is_revealed = true;
            screen->print_wrapped(secret.description_on_reveal);
            screen->println("");

            if (!secret.reveals_item_id.empty()) {
                auto item = persistency::load_item(context.gamedata_dir, secret.reveals_item_id);
                room.add_item(Storage::Entry{1, item});
            }
        }
    }
    room.set_secrets(secrets);

    return true;
}