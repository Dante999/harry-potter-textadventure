#ifndef WINDOW_SPELLS_HPP
#define WINDOW_SPELLS_HPP

#include "window_base.hpp"

#include "hpta-lib/objects/spell.hpp"

class Window_Spells : public Window_Base<Spell> {

  private:
    Spell_Cache m_spell_cache;

  public:
    Window_Spells(const std::string &name, Spell_Cache &cache) : Window_Base{name}, m_spell_cache{cache} {}

    void               create_object() override;
    void               load_object() override;
    std::vector<Spell> get_objects() override;
    void               refresh_cache() override;
    void               save_object() override;
    void               show_attributes() override;
};

#endif /* WINDOW_SPELLS_HPP */
