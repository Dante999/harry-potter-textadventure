#ifndef WINDOW_ROOMS_HPP
#define WINDOW_ROOMS_HPP

#include "event_engine.hpp"
#include "panel_base.hpp"

#include "hpta-lib/objects/room.hpp"

class Panel_Rooms : public Panel_Base<Room>, public IEvent_handler {

  private:
    Room_cache    m_room_cache;
    Event_engine &m_event_engine;

  private:
    void show_tab_room_exits();
    void show_tab_room_secrets();
    void show_tab_room_items();

  public:
    Panel_Rooms(const std::string &name, Room_cache &cache, Event_engine &event_engine)
        : Panel_Base{name}, m_room_cache{cache}, m_event_engine{event_engine}
    {
    }

    void              create_object() override;
    void              load_object() override;
    std::vector<Room> get_objects() override;
    void              refresh_cache() override;
    void              save_object() override;
    void              show_attributes() override;
    void              on_event(Event event) override;
};

#endif /* WINDOW_ROOMS_HPP */
