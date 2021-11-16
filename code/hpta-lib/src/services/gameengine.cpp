#include "services/gameengine.hpp"

#include "services/registry.hpp"
#include "visualizer.hpp"

bool Gameengine::walk(const Direction &direction)
{
	auto current_room = Registry::get_persistence().get_room(m_player->get_room_id());

	std::string new_room_id;

	// TODO: Why does 'current_room.get_exits().find(direction)' return garbage for description and room_id?
	for (const auto &i : current_room.get_exits()) {
		if (i.first == direction) {
			new_room_id = i.second.room_id;
		}
	}

	if (new_room_id.empty()) {
		return false;
	}

	auto new_room = Registry::get_persistence().get_room(new_room_id);

	m_player->set_room_id(new_room.get_id());

	Visualizer::show(new_room);

	return true;
}
