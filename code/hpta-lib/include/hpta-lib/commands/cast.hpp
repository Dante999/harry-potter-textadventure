#ifndef CAST_HPP
#define CAST_HPP

#include "hpta-lib/commands/icommand.hpp"

class Cast : public ICommand {
  public:
    const std::string get_command() override;
    const std::string get_description() override;

    bool interprete(Context &context, const std::vector<std::string> &token) override;
};

inline const std::string Cast::get_command() { return "zauber <Zauberspruch> auf <Objekt>"; }

inline const std::string Cast::get_description() { return "Bewirkt den ausgesprochenen Zauber auf das angegebene Objekt"; }

#endif /* CAST_HPP */
