#ifndef WINDOW_SPELLS_HPP
#define WINDOW_SPELLS_HPP

#include "base_window.hpp"

#include "hpta-lib/objects/spell.hpp"

class Window_Spells : public Base_Window<Spell> {

  private:
    Spell_Cache m_spell_cache;

  public:
    Window_Spells(const std::string &name, Spell_Cache &cache) : Base_Window{name}, m_spell_cache{cache} {}

    void               create_object() override;
    void               load_object(const Spell &spell) override;
    std::vector<Spell> get_objects() override;
    void               refresh_cache() override;
    void               save_object() override;
    void               show_attributes() override;
};

#endif /* WINDOW_SPELLS_HPP */
