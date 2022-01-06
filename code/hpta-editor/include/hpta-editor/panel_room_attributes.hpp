#ifndef PANEL_ROOM_ATTRIBUTES_HPP
#define PANEL_ROOM_ATTRIBUTES_HPP

#include "hpta-lib/objects/room.hpp"
#include <string>

namespace Panel_room_attributes {

void set_room(const std::string &room_id);
void set_room(Room &room);
void refresh();

} // namespace Panel_room_attributes

#endif // PANEL_ROOM_ATTRIBUTES_HPP
