#ifndef MAP_HPP
#define MAP_HPP

#include <SFML/Graphics/RenderWindow.hpp>

#include "hpta-editor/event_engine.hpp"
#include "hpta-editor/ievent_handler.hpp"
#include "hpta-editor/ipanel.hpp"
#include "object_cache.hpp"

class Map : public IPanel, public IEvent_handler {
  private:
	sf::RenderWindow &m_window;
	Room_cache &      m_room_cache;
	Event_engine &    m_event_engine;

  private:
	void init();

  public:
	Map(sf::RenderWindow &window, Room_cache &room_cache, Event_engine &event_engine)
	    : m_window{window}, m_room_cache{room_cache}, m_event_engine{event_engine}
	{
		init();
	}

	void refresh() override;
	void on_event(Event event) override;
};

#endif // MAP_HPP
