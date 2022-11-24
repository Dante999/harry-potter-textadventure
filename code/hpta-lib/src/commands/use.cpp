#include "hpta-lib/commands/use.hpp"

#include "hpta-lib/persistency/persistency.hpp"
#include "hpta-lib/services/room_cache_service.hpp"
#include "hpta-lib/services/user_interaction_service.hpp"
#include "hpta-lib/util/hpta_strings.hpp"

#include <algorithm>
#include <fmt/core.h>

bool Use::interprete(Context &context, const std::vector<std::string> &token)
{
    // benutze <Item> an <Objekt>
    const auto screen = context.service_registry.get<User_Interaction_Service>()->get_screen();

    if (!Hpta_strings::equals_one_of(token.at(0), {"benutze"}))
        return false;

    auto it_separator = std::find_if(std::begin(token), std::end(token), [](auto &word) {
        return Hpta_strings::equals_one_of(word, {"an", "auf"});
    });

    if (it_separator == std::end(token)) {
        screen->println("Worauf soll ich das Item anwenden?");
        return true;
    }

    std::string item_name;
    for (auto i = std::begin(token) + 1; i < it_separator; ++i) {
        item_name += *i + " ";
    }
    item_name = Hpta_strings::trim(item_name);

    auto items_in_inventory = context.player->get_items();
    auto item               = std::find_if(std::begin(items_in_inventory), std::end(items_in_inventory),
                             [&](auto val) { return Hpta_strings::equals_ignorecase(val.item.get_name(), item_name); });

    if (item == std::end(items_in_inventory)) {
        screen->println("Dieses Item besitzt du nicht");
        return true;
    }

    std::string target_name;
    for (auto i = it_separator + 1; i < std::end(token); ++i) {
        target_name += *i + " ";
    }
    target_name = Hpta_strings::trim(target_name);

    auto &room = context.service_registry.get<Room_cache_service>()->get_room(context.player->get_room_id());

    auto secrets = room.get_secrets();
    for (auto &secret : secrets) {
        if (!secret.is_revealed && Hpta_strings::equals_ignorecase(secret.name, target_name) &&
            Hpta_strings::equals_ignorecase(secret.needs_item_id, item->item.get_id())) {

            secret.is_revealed = true;
            screen->print_wrapped(secret.description_on_reveal);
            screen->println("");

            if (!secret.reveals_item_id.empty()) {
                auto revealed_item = persistency::load_item(context.gamedata_dir, secret.reveals_item_id);
                room.add_item(Storage::Entry{1, revealed_item});
            }
        }
    }
    room.set_secrets(secrets);

    return true;
}
