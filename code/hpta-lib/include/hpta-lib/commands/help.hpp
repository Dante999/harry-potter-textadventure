#ifndef HELP_H
#define HELP_H

#include "hpta-lib/commands/icommand.hpp"

#include <memory>
#include <vector>

class Help : public ICommand {
  private:
	std::vector<std::shared_ptr<ICommand>> &m_commands;

  public:
	explicit Help(std::vector<std::shared_ptr<ICommand>> &commands) : m_commands(commands) {}
	const std::string get_command() override;
	const std::string get_description() override;
	bool              interprete(const std::vector<std::string> &token) override;
};

inline const std::string Help::get_command()
{
	return "hilfe";
}

inline const std::string Help::get_description()
{
	return "zeigt diesen Hilfetext an";
}

#endif /* HELP_H */
