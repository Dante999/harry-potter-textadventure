#ifndef VISUALIZER_H
#define VISUALIZER_H

#include "hpta-lib/objects/item.hpp"
#include "hpta-lib/objects/player.hpp"
#include "hpta-lib/objects/room.hpp"
#include "hpta-lib/screen/iscreen.hpp"
#include "hpta-lib/util/hpta_strings.hpp"

#include <memory>

class Visualizer {
  private:
    const std::shared_ptr<IScreen> m_screen;

  public:
    explicit Visualizer(std::shared_ptr<IScreen> screen) : m_screen{screen} {};

    void show(const Room &room);
    void show(const Player &player);
    void show(const Item &item);
    void show(const Room::Detail &detail);
    void show(const Room::Secret &secret);
};

#endif
