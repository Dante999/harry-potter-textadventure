#ifndef PERSISTENCY_HPP
#define PERSISTENCY_HPP

#include "hpta-lib/objects/item.hpp"
#include "hpta-lib/objects/room.hpp"

namespace persistency {
[[nodiscard]] Room load_room(const std::string &gamedata_dir, const std::string &filepath);
[[nodiscard]] Item load_item(const std::string &gamedata_dir, const std::string &filepath);

bool save_room(const std::string &gamedata_dir, const Room &room);
bool save_item(const std::string &gamedata_dir, const Item &item);
} // namespace persistency

#endif /* PERSISTENCY_HPP */
