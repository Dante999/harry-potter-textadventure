#include "commands/look.hpp"

#include "services/registry.hpp"
#include "visualizer.hpp"

bool Look::interprete(const std::vector<std::string> &token)
{
	if (token.at(0) == "schau") {
		auto &player = Registry::get_gameengine().get_player();

		Visualizer::show(Registry::get_persistence().get_room(player->get_room_id()));
		return true;
	}

	return false;
}
