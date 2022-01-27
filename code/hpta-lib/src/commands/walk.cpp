#include "hpta-lib/commands/walk.hpp"

#include "hpta-lib/screen.hpp"
#include "hpta-lib/services/player_walk_service.hpp"
#include "hpta-lib/util/hpta_strings.hpp"

#include <algorithm>
#include <fmt/core.h>
#include <iostream>

std::string Walk::get_direction_from_single_word_command(const std::string &s)
{
	std::string word(s);
	std::transform(word.begin(), word.end(), word.begin(), ::tolower);

	if (word == "n" || word == "norden")
		return "norden";
	else if (word == "s" || word == "süden")
		return "süden";
	else if (word == "w" || word == "westen")
		return "westen";
	else if (word == "o" || word == "osten")
		return "osten";
	else
		return "";
}

bool Walk::interprete(Context &context, const std::vector<std::string> &token)
{
	std::ignore = context;

	std::string direction;

	if (token.size() == 1) {

		direction = get_direction_from_single_word_command(token.at(0));

		if (direction.empty())
			return false;
	}
	else if (token.size() == 3 && //
	         Hpta_strings::equals_ignorecase(token.at(0), "gehe") &&
	         Hpta_strings::equals_ignorecase(token.at(1), "nach")) {
		direction = token.at(2);
	}
	else {
		return false;
	}

	if (direction.empty() || !context.service_registry.get<Player_walk_service>()->walk(direction)) {
		Screen::print("dorthin kannst du nicht gehen...\n");
	}

	return true;
}
