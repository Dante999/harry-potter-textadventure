#ifndef USE_HPP
#define USE_HPP

#include "hpta-lib/commands/icommand.hpp"

class Use : public ICommand {
  public:
    const std::string get_command() override;
    const std::string get_description() override;

    bool interprete(Context &context, const std::vector<std::string> &token) override;
};

inline const std::string Use::get_command() { return "benutze <Item> an <Objekt>"; }

inline const std::string Use::get_description() { return "Benutze ein Item aus dem Inventar auf angegebenem Objekt"; }

#endif /* USE_HPP */
