#ifndef GIVE_HPP
#define GIVE_HPP

class Give : public ICommand {
  public:
    const std::string get_command() override;
    const std::string get_description() override;

    bool interprete(Context &context, const std::vector<std::string> &token) override;
};

inline const std::string Give::get_command() { return "gib <Item> [an <Objekt>]"; }

inline const std::string Give::get_description() { return "Benutze ein Item aus dem Inventar auf angegebenem Objekt"; }

#endif /* GIVE_HPP */
