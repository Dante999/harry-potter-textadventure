#ifndef LOOK_H
#define LOOK_H

#include "icommand.hpp"

class Look : public ICommand {
  public:
	const std::string get_command() override;
	const std::string get_description() override;
	bool              interprete(const std::vector<std::string> &token) override;
};

inline const std::string Look::get_command()
{
	return "schau <objekt>";
}

inline const std::string Look::get_description()
{
	return "zeige details zum Objekt";
}

#endif /* LOOK_H */
