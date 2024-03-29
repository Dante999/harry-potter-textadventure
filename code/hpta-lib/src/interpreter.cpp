#include "hpta-lib/interpreter.hpp"

#include <iostream>
#include <sstream>

#include "hpta-lib/commands/cast.hpp"
#include "hpta-lib/commands/help.hpp"
#include "hpta-lib/commands/inventory.hpp"
#include "hpta-lib/commands/look.hpp"
#include "hpta-lib/commands/say.hpp"
#include "hpta-lib/commands/take.hpp"
#include "hpta-lib/commands/use.hpp"
#include "hpta-lib/commands/walk.hpp"

Interpreter::Interpreter()
{
    m_commands.emplace_back(std::make_shared<Walk>());
    m_commands.emplace_back(std::make_shared<Look>());
    m_commands.emplace_back(std::make_shared<Inventory>());
    m_commands.emplace_back(std::make_shared<Take>());
    m_commands.emplace_back(std::make_shared<Say>());
    m_commands.emplace_back(std::make_shared<Cast>());
    m_commands.emplace_back(std::make_shared<Help>(m_commands));
    m_commands.emplace_back(std::make_shared<Use>());
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

void Interpreter::parse(Context &context, const std::string &text)
{
    if (text.empty()) {
        return;
    }

    const auto tokens = split_text_by_words(text);

    for (auto &cmd : m_commands) {
        if (cmd->interprete(context, tokens)) {
            return;
        }
    }

    std::cout << "Unknown command!\n";
}
