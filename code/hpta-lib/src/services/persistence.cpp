#include "services/persistence.hpp"

#include "persistency/room_persistency.hpp"
#include "services/registry.hpp"

Room &Persistence::get_room(const std::string &id)
{
	if (m_rooms.find(id) == m_rooms.end()) {
		auto room = Room_persistency::load(Registry::m_gamedata_dir, id);
		m_rooms.insert({room.get_id(), room});
	}

	return m_rooms.find(id)->second;
}
