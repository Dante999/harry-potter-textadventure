#ifndef ROOM_LIST_HPP
#define ROOM_LIST_HPP

#include "objects/room.hpp"

namespace Room_list {

void              refresh_rooms();
std::vector<Room> get_rooms();

} // namespace Room_list

#endif // ROOM_LIST_HPP
