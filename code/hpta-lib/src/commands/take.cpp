#include "hpta-lib/commands/take.hpp"

#include "hpta-lib/services/cache_service.hpp"
#include "hpta-lib/services/user_interaction_service.hpp"
#include "hpta-lib/util/hpta_strings.hpp"

#include <algorithm>
#include <fmt/core.h>

bool Take::interprete(Context &context, const std::vector<std::string> &token)
{
    const auto screen = context.service_registry.get<User_Interaction_Service>()->get_screen();

    if (token.at(0) != "nimm")
        return false;

    if (token.size() < 3) {
        screen->print("Was und wieviel soll ich nehmen?\n");
        return true;
    }

    const auto &str_quantity = token.at(1);
    if (str_quantity.back() != 'x') {
        screen->print("Welche Anzahl soll ich nehmen?\n");
        return true;
    }

    int quantity = std::stoi(str_quantity.substr(0, str_quantity.length() - 1));

    std::string object_name;
    for (size_t i = 2; i < token.size(); ++i) {
        object_name += token.at(i) + " ";
    }

    auto &room = context.service_registry.get<Cache_Service>()->rooms->get_object(context.player->get_room_id());

    const auto &storage_entries = room.get_items();

    const auto result = std::find_if(storage_entries.begin(), storage_entries.end(), [&object_name](auto &i) {
        return Hpta_strings::equals_ignorecase(i.item.get_name(), Hpta_strings::trim(object_name));
    });

    if (result == storage_entries.end()) {
        screen->print("Diese Item finde ich nicht\n");
        return true;
    }

    // copy before removing it, otherwise you will get garbage
    Item item{result->item};

    const auto removed_quantity = room.remove_item({quantity, item});
    context.player->add_item({removed_quantity, item});

    screen->print(fmt::format("{}x {} aufgenommen!\n\n", removed_quantity, item.get_name()));

    return true;
}
