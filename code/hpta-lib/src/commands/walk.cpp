#include "commands/walk.hpp"

#include "screen.hpp"
#include "services/registry.hpp"
#include "util/hpta_strings.hpp"

#include <fmt/core.h>
#include <iostream>

Direction Walk::str_to_direction(const std::string &s)
{
	std::string word(s);
	std::transform(word.begin(), word.end(), word.begin(), ::tolower);

	if (word == "n" || word == "norden")
		return Direction::NORTH;
	else if (word == "s" || word == "süden")
		return Direction::SOUTH;
	else if (word == "w" || word == "westen")
		return Direction::WEST;
	else if (word == "o" || word == "osten")
		return Direction::EAST;
	else
		return Direction::UNDEFINED;
}

bool Walk::interprete(const std::vector<std::string> &token)
{

	Direction d = Direction::UNDEFINED;

	if (token.size() == 1) {
		d = str_to_direction(token.at(0));
	}
	else if (token.size() == 3 && //
	         Hpta_strings::equals_ignorecase(token.at(0), "gehe") &&
	         Hpta_strings::equals_ignorecase(token.at(1), "nach")) {

		d = str_to_direction(token.at(2));
	}
	else {
		return false;
	}

	if (d == Direction::UNDEFINED || !Registry::get_gameengine().walk(d)) {
		Screen::print("dorthin kannst du nicht gehen...\n");
	}

	return true;
}
