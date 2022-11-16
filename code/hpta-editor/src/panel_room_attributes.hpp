#ifndef PANEL_ROOM_ATTRIBUTES_HPP
#define PANEL_ROOM_ATTRIBUTES_HPP

#include "hpta-lib/objects/room.hpp"
#include <string>

#include "event_engine.hpp"
#include "ipanel.hpp"

class Panel_room_attributes : public IPanel, public IEvent_handler {

  private:
    Event_engine &m_event_engine;

  private:
    void save_room();
    void show_exit_tab_content();
    void show_item_tab_content();
    void show_detail_tab_content();

  public:
    explicit Panel_room_attributes(Event_engine &event_engine) : m_event_engine{event_engine} {}

    void set_room(const std::string &room_id);
    void set_room(Room &room);

    void refresh() override;
    void on_event(Event event) override;
};

#endif // PANEL_ROOM_ATTRIBUTES_HPP
