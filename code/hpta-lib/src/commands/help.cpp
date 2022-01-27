#include "hpta-lib/commands/help.hpp"

#include "hpta-lib/screen.hpp"
#include "hpta-lib/util/hpta_strings.hpp"

#include <algorithm>
#include <fmt/color.h>
#include <fmt/core.h>

bool Help::interprete(Context &context, const std::vector<std::string> &token)
{
	std::ignore = context;

	const auto &word = token.at(0);

	if (word != "hilfe")
		return false;

	for (auto &cmd : m_commands) {
		Screen::print(fmt::format(fmt::emphasis::bold, "{}\n", cmd->get_command()));
		const auto lines =
		    Hpta_strings::split_text_into_lines(cmd->get_description(), Screen::column_width - Screen::tab_width);

		for (const auto &line : lines) {
			Screen::print(fmt::format("\t{}\n", line));
		}

		Screen::print("\n");
	}

	return true;
}
