#ifndef PANEL_ITEM_ATTRIBUTES_HPP
#define PANEL_ITEM_ATTRIBUTES_HPP

#include "hpta-lib/objects/item.hpp"
#include <string>

#include "hpta-editor/event_engine.hpp"
#include "hpta-editor/ipanel.hpp"

class Panel_item_attributes : public IPanel, public IEvent_handler {

  private:
    Event_engine &m_event_engine;

  private:
    void save_room();
    void show_exit_tab_content();
    void show_item_tab_content();

  public:
    explicit Panel_item_attributes(Event_engine &event_engine) : m_event_engine{event_engine} {}

    void set_item(const std::string &item_id);
    void set_item(Item &item);

    void refresh() override;
    void on_event(Event event) override;
};

#endif // PANEL_ITEM_ATTRIBUTES_HPP
