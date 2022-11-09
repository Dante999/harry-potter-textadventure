#include "hpta-lib/commands/look.hpp"

#include "hpta-lib/services/room_cache_service.hpp"
#include "hpta-lib/services/user_interaction_service.hpp"
#include "hpta-lib/util/hpta_strings.hpp"

bool Look::interprete(Context &context, const std::vector<std::string> &token)
{
    auto &room = context.service_registry.get<Room_cache_service>()->get_room(context.player->get_room_id());

    const auto visualizer = context.service_registry.get<User_Interaction_Service>()->get_visualizer();
    const auto screen     = context.service_registry.get<User_Interaction_Service>()->get_screen();

    if (!Hpta_strings::equals_one_of(token.at(0), {"schau", "untersuche"}))
        return false;

    if (token.size() == 1) {
        visualizer->show(room);
        return true;
    }

    std::string object_name;
    for (size_t i = 1; i < token.size(); ++i) {
        object_name += token.at(i) + " ";
    }

    object_name = Hpta_strings::rtrim(object_name);

    for (const auto &item : room.get_items()) {
        if (Hpta_strings::equals_ignorecase(item.item.get_name(), object_name)) {
            visualizer->show(item.item);
            return true;
        }
    }

    for (const auto &detail : room.get_details()) {
        if (Hpta_strings::equals_ignorecase(detail.name, object_name)) {
            visualizer->show(detail);
            return true;
        }
    }

    screen->print("So etwas siehst du dort nicht...\n");

    return true;
}
