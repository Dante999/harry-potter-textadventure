#ifndef WINDOW_SPELLS_HPP
#define WINDOW_SPELLS_HPP

#include "panel_base.hpp"

#include "hpta-lib/objects/spell.hpp"

class Panel_Spells : public Panel_Base<Spell> {

  private:

  public:
    Panel_Spells(const std::string &name, World_Cache &world_cache) : Panel_Base{name, world_cache} {}

    void               create_object() override;
    void               load_object() override;
    std::vector<Spell> get_objects() override;
    void               refresh_cache() override;
    void               save_object() override;
    void               show_attributes() override;
};

#endif /* WINDOW_SPELLS_HPP */
