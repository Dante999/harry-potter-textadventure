#ifndef EVENT_ENGINE_HPP
#define EVENT_ENGINE_HPP

#include "ievent_handler.hpp"

#include <memory>
#include <vector>

class Event_engine {

  private:
    std::vector<std::shared_ptr<IEvent_handler>> m_event_handler;

  public:
    void add_event_handler(std::shared_ptr<IEvent_handler> handler);
    void publish(Event event);
};

#endif // EVENT_ENGINE_HPP
