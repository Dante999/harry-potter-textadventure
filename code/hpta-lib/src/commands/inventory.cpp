#include "hpta-lib/commands/inventory.hpp"

#include "hpta-lib/screen.hpp"
#include "hpta-lib/util/hpta_strings.hpp"
#include "hpta-lib/visualizer.hpp"

#include <fmt/core.h>

bool Inventory::interprete(Context &context, const std::vector<std::string> &token)
{

	const auto &word = token.at(0);

	if (token.size() == 1 && Hpta_strings::equals_ignorecase(word, "inventar")) {
		Visualizer::show(*context.player);
		return true;
	}

	return false;
}
