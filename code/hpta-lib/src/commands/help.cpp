#include "hpta-lib/commands/help.hpp"

#include "hpta-lib/screen.hpp"
#include "hpta-lib/util/hpta_strings.hpp"

#include <algorithm>
#include <fmt/color.h>
#include <fmt/core.h>

bool Help::interprete(const std::vector<std::string> &token)
{

	const auto &word = token.at(0);

	if (word != "hilfe")
		return false;

	//	auto max_cmd_length = std::max_element(m_commands.begin(), m_commands.end(), [](const auto &a, const auto &b) {
	//		return a->get_command().length() > b->get_command().length();
	//	});

	//	size_t max_cmd_length = 0;

	//	for (auto &cmd : m_commands) {
	//		max_cmd_length = std::max(max_cmd_length, cmd->get_command().length());
	//	}

	//	Screen::print(fmt::format("longest cmd: {}\n", max_cmd_length));

	for (auto &cmd : m_commands) {
		Screen::print(fmt::format(fmt::emphasis::bold, "{}\n", cmd->get_command()));
		const auto lines = Hpta_strings::split_text_into_lines(cmd->get_description(), Screen::column_width - 8);

		for (const auto &line : lines) {
			Screen::print(fmt::format("\t{}\n", line));
		}

		Screen::print("\n");
	}

	return true;
}
