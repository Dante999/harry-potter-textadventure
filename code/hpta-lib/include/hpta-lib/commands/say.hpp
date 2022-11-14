#ifndef SAY_HPP
#define SAY_HPP

#include "hpta-lib/commands/icommand.hpp"

class Say : public ICommand {
  public:
    const std::string get_command() override;
    const std::string get_description() override;

    bool interprete(Context &context, const std::vector<std::string> &token) override;
};

inline const std::string Say::get_command() { return "sag <Text>"; }

inline const std::string Say::get_description() { return "Sprich den angegebenen Text für alle höhrbar in den Raum"; }

#endif /* SAY_HPP */
