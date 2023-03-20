#include "hpta-lib/services/player_walk_service.hpp"

#include "hpta-lib/services/cache_service.hpp"
#include "hpta-lib/services/user_interaction_service.hpp"
#include "hpta-lib/util/hpta_strings.hpp"
#include "hpta-lib/visualizer.hpp"

bool Player_walk_service::walk(const std::string &direction)
{
    auto       cache = m_service_registry.get<Cache_Service>();
    const auto visualizer = m_service_registry.get<User_Interaction_Service>()->get_visualizer();

    auto current_room = cache->rooms->get_object(m_player->get_room_id());

    std::string new_room_id;

    for (const auto &i : current_room.get_exits()) {
        if (Hpta_strings::equals_ignorecase(i.direction, direction)) {
            new_room_id = i.room_id;
        }
    }

    if (new_room_id.empty()) {
        return false;
    }

    auto new_room = cache->rooms->get_object(new_room_id);

    m_player->set_room_id(new_room.get_id());

    visualizer->show(new_room);

    return true;
}
