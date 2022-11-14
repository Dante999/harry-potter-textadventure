#include "hpta-editor/event_engine.hpp"

#include <spdlog/spdlog.h>

void Event_engine::add_event_handler(std::shared_ptr<IEvent_handler> handler) { m_event_handler.emplace_back(handler); }

void Event_engine::publish(Event event)
{
    spdlog::info("publishing event {}", event.event_type);

    for (auto &handler : m_event_handler) {
        handler->on_event(event);
    }
}
