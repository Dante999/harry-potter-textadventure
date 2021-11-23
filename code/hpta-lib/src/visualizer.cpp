#include "visualizer.hpp"

#include <fmt/core.h>

#include "util/hpta_strings.hpp"

namespace Visualizer {
auto direction_to_string(Direction direction)
{
	switch (direction) {
	case Direction::NORTH:
		return "Norden";
	case Direction::SOUTH:
		return "Süden";
	case Direction::EAST:
		return "Osten";
	case Direction::WEST:
		return "Westen";
	default:
		return "Unbekannt";
	}
}

void show(const Room &room)
{
	Screen::box_start(room.get_name());

	for (const auto &line : Hpta_strings::split_text_into_lines(room.get_description(), Screen::column_width)) {
		Screen::print(line + "\n");
	}

	Screen::print("\n");

	if (!room.get_items().empty()) {
		Screen::print("In deiner Umgebung befindet sich: \n");
		for (auto &item : room.get_items()) {
			Screen::print(fmt::format("\t{}x {}\n", item.quantity, item.item.get_name()));
		}
	}

	Screen::print("\n");
	Screen::print("Mögliche Richtungen:\n");
	for (const auto &direction : room.get_exits()) {
		Screen::print(fmt::format("\t{}\t-> {}\n", direction_to_string(direction.first), direction.second.description));
	}

	Screen::box_end();
}

void show(const Player &player)
{
	Screen::box_start(player.get_name());
	Screen::print(fmt::format("Stärke ............ {}\n", player.get_strength()));
	Screen::print(fmt::format("Geschicklichkeit .. {}\n", player.get_dextery()));
	Screen::print(fmt::format("Vitalität ......... {}\n", player.get_vitality()));
	Screen::print(fmt::format("Magie ............. {}\n", player.get_magic()));
	Screen::box_end();
}

void show(const Item &item)
{
	Screen::box_start(item.get_name());

	for (const auto &line : Hpta_strings::split_text_into_lines(item.get_description(), Screen::column_width)) {
		Screen::print(line + "\n");
	}

	Screen::box_end();
}

} // namespace Visualizer
