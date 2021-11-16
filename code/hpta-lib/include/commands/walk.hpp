#ifndef WALK_H
#define WALK_H

#include "icommand.hpp"

class Walk : public ICommand {
  public:
	const std::string get_command() override;
	const std::string get_description() override;
	bool              interprete(const std::vector<std::string> &token) override;
};

inline const std::string Walk::get_command()
{
	return "n|s|o|w";
}

inline const std::string Walk::get_description()
{
	return "gehe nach Norden, Süden, Osten oder Westen";
}

#endif /* WALK_H */
