#include "commands/walk.hpp"

#include "screen.hpp"
#include "services/registry.hpp"

#include <fmt/core.h>

bool Walk::interprete(const std::vector<std::string> &token)
{
	const auto &word = token.at(0);
	Direction   d;

	if (word == "n")
		d = Direction::NORTH;
	else if (word == "s")
		d = Direction::SOUTH;
	else if (word == "w")
		d = Direction::WEST;
	else if (word == "o")
		d = Direction::EAST;
	else
		return false;

	if (!Registry::get_gameengine().walk(d)) {
		Screen::print("dorthin kannst du nicht gehen...\n");
	}

	return true;
}
