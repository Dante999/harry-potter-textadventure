#include "hpta-lib/commands/say.hpp"

#include "hpta-lib/persistency/persistency.hpp"
#include "hpta-lib/services/cache_service.hpp"
#include "hpta-lib/services/user_interaction_service.hpp"
#include "hpta-lib/util/hpta_strings.hpp"

#include <fmt/core.h>

bool Say::interprete(Context &context, const std::vector<std::string> &token)
{
    const auto screen = context.service_registry.get<User_Interaction_Service>()->get_screen();

    if (!Hpta_strings::equals_one_of(token.at(0), {"sag", "sprich"}))
        return false;

    std::string text{};

    for (size_t i = 1; i < token.size(); ++i) {
        text += token.at(i);
    }

    auto &room = context.service_registry.get<Cache_Service>()->rooms->get_object(context.player->get_room_id());

    auto secrets = room.get_secrets();
    for (auto &secret : secrets) {
        if (!secret.is_revealed && Hpta_strings::equals_ignorecase(secret.needs_password, text)) {
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
