#ifndef PERSISTENCE_H
#define PERSISTENCE_H

#include <map>
#include <string>

#include "hpta-lib/objects/room.hpp"

class Persistence {

  private:
	std::map<std::string, Room> m_rooms;

  public:
	Room &get_room(const std::string &id);
};

#endif /* PERSISTENCE_H */
