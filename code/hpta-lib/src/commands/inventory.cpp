#include "hpta-lib/commands/inventory.hpp"

#include "hpta-lib/services/user_interaction_service.hpp"
#include "hpta-lib/util/hpta_strings.hpp"

#include <fmt/core.h>

bool Inventory::interprete(Context &context, const std::vector<std::string> &token)
{
    const auto visualizer = context.service_registry.get<User_Interaction_Service>()->get_visualizer();

    const auto &word = token.at(0);

    if (token.size() == 1 && Hpta_strings::equals_ignorecase(word, "inventar")) {
        visualizer->show(*context.player);
        return true;
    }

    return false;
}
