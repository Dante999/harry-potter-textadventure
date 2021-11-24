#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include "icommand.hpp"

class Inventory : public ICommand {
  public:
	const std::string get_command() override;
	const std::string get_description() override;
	bool              interprete(const std::vector<std::string> &token) override;
};

inline const std::string Inventory::get_command()
{
	return "inventar";
}

inline const std::string Inventory::get_description()
{
	return "zeige das Inventar an";
}

#endif /* INVENTORY_HPP */
