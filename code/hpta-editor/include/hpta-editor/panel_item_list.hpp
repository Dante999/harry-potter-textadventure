#ifndef PANEL_ITEM_LIST_HPP
#define PANEL_ITEM_LIST_HPP

#include <string>

#include "hpta-editor/event_engine.hpp"
#include "hpta-editor/ipanel.hpp"
#include "hpta-editor/object_cache.hpp"

class Panel_item_list : public IPanel {
  private:
    Item_cache &  m_item_cache;
    float         m_scale_factor;
    Event_engine &m_event_engine;

  public:
    Panel_item_list(Item_cache &item_cache, Event_engine &event_engine)
        : m_item_cache{item_cache}, m_event_engine{event_engine}
    {
        m_scale_factor = Hpta_config::get_float(Settings::scale_factor);
    }

    void refresh() override;
};

#endif // PANEL_ITEM_LIST_HPP
