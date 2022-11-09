#ifndef PANEL_ROOM_LIST_HPP
#define PANEL_ROOM_LIST_HPP

#include <string>

#include "hpta-editor/event_engine.hpp"
#include "hpta-editor/ipanel.hpp"
#include "hpta-editor/object_cache.hpp"
#include "hpta-editor/panel_room_attributes.hpp"

class Panel_room_list : public IPanel {

  private:
    Room_cache &  m_room_cache;
    Event_engine &m_event_engine;

    float m_scale_factor;

  public:
    Panel_room_list(Room_cache &room_cache, Event_engine &event_engine)
        : m_room_cache{room_cache}, m_event_engine{event_engine}
    {
        m_scale_factor = Hpta_config::get_float(Settings::scale_factor);
    }

    void refresh() override;
};
#endif // PANEL_ROOM_LIST_HPP
