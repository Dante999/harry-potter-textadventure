#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include "hpta-lib/commands/icommand.hpp"

class Inventory : public ICommand {
  public:
	const std::string get_command() override;
	const std::string get_description() override;
	bool              interprete(Context &context, const std::vector<std::string> &token) override;
};

inline const std::string Inventory::get_command()
{
	return "inventar";
}

inline const std::string Inventory::get_description()
{
	return "zeigt den Inhalt deines Inventars an.";
}

#endif /* INVENTORY_HPP */
