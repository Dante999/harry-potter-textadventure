#ifndef VISUALIZER_H
#define VISUALIZER_H

#include "objects/player.hpp"
#include "objects/room.hpp"
#include "screen.hpp"

namespace Visualizer {
void show(const Room &room);
void show(const Player &player);
} // namespace Visualizer

#endif /* VISUALIZER_H */
