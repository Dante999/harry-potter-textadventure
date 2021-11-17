#ifndef PANEL_ROOM_ATTRIBUTES_HPP
#define PANEL_ROOM_ATTRIBUTES_HPP

#include <string>

namespace Panel_room_attributes {

void set_gamedata_dir(const std::string &gamedata_dir);
void set_room(const std::string &room_id);
void refresh();

} // namespace Panel_room_attributes

#endif // PANEL_ROOM_ATTRIBUTES_HPP
