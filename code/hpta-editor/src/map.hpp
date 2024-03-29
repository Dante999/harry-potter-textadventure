#ifndef MAP_HPP
#define MAP_HPP

#include <SFML/Graphics/RenderWindow.hpp>

#include "event_engine.hpp"
#include "ievent_handler.hpp"
#include "ipanel.hpp"
#include "object_cache.hpp"

class Map : public IEvent_handler {
  private:
    sf::RenderWindow &m_window;
    World_Cache &     m_world_cache;
    Event_engine &    m_event_engine;

  private:
    void init();

  public:
    explicit Map(sf::RenderWindow &window, World_Cache &world_cache, Event_engine &event_engine)
        : m_window{window}, m_world_cache{world_cache}, m_event_engine{event_engine}
    {
        init();
    }

    void refresh();
    void on_event(Event event) override;
};

#endif // MAP_HPP
