#ifndef IEVENT_HPP
#define IEVENT_HPP

#include <string>

class Event {
  public:
	enum class Type { ROOM_CHANGED, ROOM_SELECTED, CREATE_ROOM } event_type;

	std::string room_id = "";
};

class IEvent_handler {
  public:
	virtual void on_event(Event event) = 0;
	virtual ~IEvent_handler()          = default;
};

#endif // IEVENT_HPP
