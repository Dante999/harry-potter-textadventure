#ifndef LOOK_H
#define LOOK_H

#include "hpta-lib/commands/icommand.hpp"

class Look : public ICommand {
  public:
	const std::string get_command() override;
	const std::string get_description() override;

	bool interprete(Context &context, const std::vector<std::string> &token) override;
};

inline const std::string Look::get_command()
{
	return "untersuche <objekt>";
}

inline const std::string Look::get_description()
{
	return "zeigt details zum genannten Objekt. Alternativ zu 'untersuche' kann auch das Wort 'schau' verwendet "
	       "werden.";
}

#endif /* LOOK_H */
