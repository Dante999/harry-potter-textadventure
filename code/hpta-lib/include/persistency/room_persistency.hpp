#ifndef ROOM_PERSISTENCY_H
#define ROOM_PERSISTENCY_H

#include "directions.hpp"
#include "objects/room.hpp"

class Room_persistency {
  public:
	static Direction   deserialize_direction(const std::string &direction);
	static std::string serialize_direction(const Direction direction);

	static Room load(const std::string &gamedata_dir, const std::string &filepath);
	static bool save(const std::string &gamedata_dir, const Room &room);
};

#endif /* ROOM_PERSISTENCY_H */
