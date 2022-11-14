#ifndef TAKE_HPP
#define TAKE_HPP

#include "hpta-lib/commands/icommand.hpp"

class Take : public ICommand {
  public:
    const std::string get_command() override;
    const std::string get_description() override;

    bool interprete(Context &context, const std::vector<std::string> &token) override;
};

inline const std::string Take::get_command() { return "nimm <anzahl>x <objekt> [von <Behälter>]"; }

inline const std::string Take::get_description()
{
    return "Nimmt das Objekt in der angegebenen Anzahl aus dem entsprechenden Behälter und legt es im Inventar ab. "
           "Wird kein behälter angegeben, wird versucht das Item aus der Umgebung genommen.";
}

#endif // TAKE_HPP
