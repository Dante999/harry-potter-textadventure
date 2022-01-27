#include "hpta-lib/services/room_cache_service.hpp"

#include "hpta-lib/persistency/room_persistency.hpp"

Room &Room_cache_service::get_room(const std::string &id)
{
	if (m_rooms.find(id) == m_rooms.end()) {
		auto room = Room_persistency::load(m_gamedata_dir, id);
		m_rooms.insert({room.get_id(), room});
	}

	return m_rooms.find(id)->second;
}
