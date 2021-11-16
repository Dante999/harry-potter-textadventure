#include "visualizer.hpp"

#include <fmt/core.h>

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

auto break_text_to_lines(std::string text)
{
	std::vector<std::string> lines;

	if (text.length() < Screen::column_width) {
		lines.emplace_back(text);
		return lines;
	}

	size_t idx_line = 0;
	size_t idx_old  = 0;
	size_t idx_new  = text.find(' ', idx_line);

	while (idx_new != std::string::npos) {
		if (idx_new - idx_line < Screen::column_width) {
			idx_old = idx_new;
		}
		else {
			lines.emplace_back(text.substr(idx_line, idx_old - idx_line));
			idx_line = idx_old + 1;
		}

		idx_new = text.find(' ', idx_new + 1);

		if (idx_new == std::string::npos) {
			lines.emplace_back(text.substr(idx_line, text.length() - idx_line));
		}
	}

	return lines;
}

void show(const Room &room)
{
	Screen::box_start(room.get_name());

	for (const auto &line : break_text_to_lines(room.get_description())) {
		Screen::print(line + "\n");
	}

	Screen::print("\n");
	for (const auto &direction : room.get_exits()) {
		Screen::print(fmt::format("{}\t-> {}\n", direction_to_string(direction.first), direction.second.description));
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
} // namespace Visualizer
