#include "hpta-lib/objects/actions.hpp"

#include "hpta-lib/persistency/persistency.hpp"
#include "hpta-lib/services/user_interaction_service.hpp"
#include "hpta-lib/services/cache_service.hpp"

#include <fmt/format.h>
#include <iostream>

struct Print_Action {
    std::string text;

    void operator()(Context &context)
    {
        const auto screen = context.service_registry.get<User_Interaction_Service>()->get_screen();

        for (const auto &line : Hpta_strings::split_text_into_lines(text, screen->column_width)) {
            screen->print(line + "\n");
        }
    }
};

struct Drop_Item_Action {
    std::string item_id;

    void operator()(Context &context)
    {
        
        auto &room = context.service_registry.get<Cache_Service>()->rooms->get_object(context.player->get_room_id());
        auto  item = persistency::load_item(context.gamedata_dir, item_id);

        room.add_item(Storage::Entry{1, item});
        
        const auto screen = context.service_registry.get<User_Interaction_Service>()->get_screen();
        screen->println(fmt::format("Deiner Umgebung wurde '{}' hinzugefügt", item.get_name()));
    }
};

std::optional<Action> create_action(const std::string &action_id, std::any value)
{

    if (action_id == "print")
        return Print_Action{std::any_cast<std::string>(value)};
    if (action_id == "drop_item")
        return Drop_Item_Action{std::any_cast<std::string>(value)};

    else
        return std::nullopt;
}
