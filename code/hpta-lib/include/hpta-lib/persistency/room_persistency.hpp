#ifndef ROOM_PERSISTENCY_H
#define ROOM_PERSISTENCY_H

#include "hpta-lib/objects/room.hpp"

class Room_persistency {
  public:
	static Room load(const std::string &gamedata_dir, const std::string &filepath);
	static bool save(const std::string &gamedata_dir, const Room &room);
};

#endif /* ROOM_PERSISTENCY_H */
