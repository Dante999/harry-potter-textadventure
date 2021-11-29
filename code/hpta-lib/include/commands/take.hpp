#ifndef TAKE_HPP
#define TAKE_HPP

#include "icommand.hpp"

class Take : public ICommand {
  public:
	const std::string get_command() override;
	const std::string get_description() override;
	bool              interprete(const std::vector<std::string> &token) override;
};

inline const std::string Take::get_command()
{
	return "nimm <anzahl>x <objekt>";
}

inline const std::string Take::get_description()
{
	return "lege Objekt in das Inventar (nimm 11x Knut)";
}

#endif // TAKE_HPP
