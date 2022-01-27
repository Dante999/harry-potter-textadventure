#ifndef WALK_H
#define WALK_H

#include "hpta-lib/commands/icommand.hpp"

class Walk : public ICommand {
  private:
	static std::string get_direction_from_single_word_command(const std::string &s);

  public:
	const std::string get_command() override;
	const std::string get_description() override;

	bool interprete(Context &context, const std::vector<std::string> &token) override;
};

inline const std::string Walk::get_command()
{
	return "gehe nach <richtung>";
}

inline const std::string Walk::get_description()
{
	return "gehe in die entsprechende Richtung, z.B. nach Norden, Süden, Osten oder Westen. Alternativ kann auch nur "
	       "die Richtung angegeben werden ohne das vorangehende 'gehe nach'. Zusätzlich gibt es noch die Möglichkeit "
	       "die Himmelsrichtungen mit n,s,o oder w abzukürzen";
}

#endif /* WALK_H */
