#include "commands/look.hpp"

#include "services/registry.hpp"
#include "util/hpta_strings.hpp"
#include "visualizer.hpp"

bool Look::interprete(const std::vector<std::string> &token)
{
	auto &player = Registry::get_gameengine().get_player();
	auto &room   = Registry::get_persistence().get_room(player->get_room_id());

	if (!Hpta_strings::equals_one_of(token.at(0), {"schau", "untersuche"}))
		return false;

	if (token.size() == 1) {
		Visualizer::show(room);
		return true;
	}

	std::string object_name;
	for (size_t i = 1; i < token.size(); ++i) {
		object_name += token.at(i) + " ";
	}

	object_name = Hpta_strings::rtrim(object_name);

	for (const auto &item : room.get_items()) {
		if (Hpta_strings::equals_ignorecase(item.item.get_name(), object_name)) {
			Visualizer::show(item.item);
			return true;
		}
	}

	Screen::print("So etwas siehst du dort nicht...\n");
	return true;
}
