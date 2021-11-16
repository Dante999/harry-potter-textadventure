#include "commands/help.hpp"

#include "screen.hpp"

#include <fmt/core.h>

bool Help::interprete(const std::vector<std::string> &token)
{

	const auto &word = token.at(0);

	if (word != "hilfe")
		return false;

	for (auto &cmd : m_commands) {
		Screen::print(fmt::format("{}\t\t\t{}\n", cmd->get_command(), cmd->get_description()));
	}

	return true;
}
