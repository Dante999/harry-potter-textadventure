#include "hpta-lib/services/player_walk_service.hpp"

#include "hpta-lib/services/room_cache_service.hpp"
#include "hpta-lib/util/hpta_strings.hpp"
#include "hpta-lib/visualizer.hpp"

bool Player_walk_service::walk(const std::string &direction)
{
	auto room_cache = m_service_registry.get<Room_cache_service>();

	auto current_room = room_cache->get_room(m_player->get_room_id());

	std::string new_room_id;

	for (const auto &i : current_room.get_exits()) {
		if (Hpta_strings::equals_ignorecase(i.direction, direction)) {
			new_room_id = i.room_id;
		}
	}

	if (new_room_id.empty()) {
		return false;
	}

	auto new_room = room_cache->get_room(new_room_id);

	m_player->set_room_id(new_room.get_id());

	Visualizer::show(new_room);

	return true;
}
