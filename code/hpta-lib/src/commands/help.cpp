#include "hpta-lib/commands/help.hpp"

#include "hpta-lib/services/user_interaction_service.hpp"
#include "hpta-lib/util/hpta_strings.hpp"

#include <algorithm>
#include <fmt/color.h>
#include <fmt/core.h>

bool Help::interprete(Context &context, const std::vector<std::string> &token)
{
    std::ignore = context;

    const auto screen = context.service_registry.get<User_Interaction_Service>()->get_screen();

    const auto &word = token.at(0);

    if (word != "hilfe")
        return false;

    for (auto &cmd : m_commands) {

        screen->print(fmt::format(fmt::emphasis::bold, "{}\n", cmd->get_command()));
        const auto lines = Hpta_strings::split_text_into_lines(
            cmd->get_description(), static_cast<size_t>(screen->column_width - screen->tab_width));

        for (const auto &line : lines) {
            screen->print(fmt::format("\t{}\n", line));
        }

        screen->print("\n");
    }

    return true;
}
