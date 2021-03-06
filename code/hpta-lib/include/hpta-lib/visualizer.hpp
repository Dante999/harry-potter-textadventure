#ifndef VISUALIZER_H
#define VISUALIZER_H

#include "hpta-lib/objects/item.hpp"
#include "hpta-lib/objects/player.hpp"
#include "hpta-lib/objects/room.hpp"
#include "hpta-lib/screen.hpp"
#include "hpta-lib/util/hpta_strings.hpp"

namespace Visualizer {
void show(const Room &room);
void show(const Player &player);
void show(const Item &item);
void show(const Room::Detail &detail);
} // namespace Visualizer

#endif /* VISUALIZER_H */
