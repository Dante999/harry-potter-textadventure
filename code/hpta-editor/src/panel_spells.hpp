#ifndef PANEL_SPELLS_HPP
#define PANEL_SPELLS_HPP

#include <string>

#include "event_engine.hpp"
#include "ipanel.hpp"
#include "object_cache.hpp"

class Panel_Spells : public IPanel {
  private:
    Spell_Cache & m_spell_cache;
    float         m_scale_factor;
    Event_engine &m_event_engine;

  private:
    void load_spell_attributes(const Spell &spell);
    void save_spell_attributes(Spell &spell);
    void show_spell_list();
    void show_spell_attributes();

  public:
    Panel_Spells(Spell_Cache &spell_cache, Event_engine &event_engine)
        : m_spell_cache{spell_cache}, m_event_engine{event_engine}
    {
        m_scale_factor = Hpta_config::get_float(Settings::scale_factor);
    }

    void refresh() override;
};

#endif /* PANEL_SPELLS_HPP */
