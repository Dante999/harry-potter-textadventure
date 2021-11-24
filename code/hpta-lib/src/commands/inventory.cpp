#include "commands/inventory.hpp"

#include "screen.hpp"
#include "services/registry.hpp"
#include "util/hpta_strings.hpp"
#include "visualizer.hpp"

#include <fmt/core.h>

bool Inventory::interprete(const std::vector<std::string> &token)
{

	const auto &word = token.at(0);

	if (token.size() == 1 && Hpta_strings::equals_ignorecase(word, "inventar")) {
		Visualizer::show(*Registry::get_gameengine().get_player());
		return true;
	}

	return false;
}
