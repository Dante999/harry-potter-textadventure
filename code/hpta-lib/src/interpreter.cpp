#include "interpreter.hpp"

#include <iostream>
#include <sstream>

#include "commands/help.hpp"
#include "commands/inventory.hpp"
#include "commands/look.hpp"
#include "commands/walk.hpp"

Interpreter::Interpreter()
{
	m_commands.emplace_back(std::make_shared<Walk>());
	m_commands.emplace_back(std::make_shared<Look>());
	m_commands.emplace_back(std::make_shared<Inventory>());
	m_commands.emplace_back(std::make_shared<Help>(m_commands));
}

const std::vector<std::string> Interpreter::split_text_by_words(const std::string &text)
{
	std::stringstream        ss(text);
	std::vector<std::string> out;

	std::string s;
	while (std::getline(ss, s, ' ')) {
		out.push_back(s);
	}

	return out;
}

void Interpreter::parse(const std::string &text)
{
	if (text.empty()) {
		return;
	}

	const auto tokens = split_text_by_words(text);

	for (auto &cmd : m_commands) {
		if (cmd->interprete(tokens)) {
			return;
		}
	}

	std::cout << "Unknown command!\n";
}
