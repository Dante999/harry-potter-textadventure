#ifndef VISUALIZER_H
#define VISUALIZER_H

#include "objects/item.hpp"
#include "objects/player.hpp"
#include "objects/room.hpp"
#include "screen.hpp"

namespace Visualizer {
void show(const Room &room);
void show(const Player &player);
void show(const Item &item);
} // namespace Visualizer

#endif /* VISUALIZER_H */
