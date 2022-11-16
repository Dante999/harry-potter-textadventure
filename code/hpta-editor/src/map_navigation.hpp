#ifndef MAP_NAVIGATION_HPP
#define MAP_NAVIGATION_HPP

#include "ievent_handler.hpp"

#include <SFML/Graphics/View.hpp>

class Map_navigation {
  private:
    sf::View &m_view;
    bool      m_has_focus{true};

  public:
    explicit Map_navigation(sf::View &view) : m_view{view} {}

    bool is_map_focused();
    void handle();
};

#endif // MAP_NAVIGATION_HPP
