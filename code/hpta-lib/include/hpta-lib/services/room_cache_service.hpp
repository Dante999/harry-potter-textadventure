#ifndef ROOM_CACHE_SERVICE_HPP
#define ROOM_CACHE_SERVICE_HPP

#include <map>
#include <string>

#include "hpta-lib/objects/room.hpp"

class Room_cache_service {

  private:
    std::map<std::string, Room> m_rooms;
    const std::string           m_gamedata_dir;

  public:
    explicit Room_cache_service(const std::string &gamedata_dir) : m_gamedata_dir{gamedata_dir} {}

    Room &get_room(const std::string &id);
};

#endif // ROOM_CACHE_SERVICE_HPP
