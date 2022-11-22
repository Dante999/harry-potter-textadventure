#include "map_navigation.hpp"

#include <imgui.h>

bool Map_navigation::is_map_focused()
{
    ImGuiFocusedFlags flags = ImGuiFocusedFlags_::ImGuiFocusedFlags_AnyWindow;
    return !ImGui::IsWindowFocused(flags);
}

void Map_navigation::handle()
{
    static auto old_position = sf::Mouse::getPosition();

    if (is_map_focused()) {

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            const auto new_position = sf::Mouse::getPosition();
            m_view.move(static_cast<float>(old_position.x - new_position.x),
                        static_cast<float>(old_position.y - new_position.y));

            old_position = sf::Mouse::getPosition();
        }
        else {
            old_position = sf::Mouse::getPosition();
        }
    }
    else if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        // save new mouse position if the user clicks from a window into the map again, otherwise the map
        // would go nuts and jumps from the old location to that one.
        old_position = sf::Mouse::getPosition();
    }
}

void Map_navigation::handle(sf::Event::MouseWheelScrollEvent mousewheelscrool)
{

    if (mousewheelscrool.wheel == sf::Mouse::VerticalWheel && is_map_focused()) {

        if (mousewheelscrool.delta > 0) {
            m_view.zoom(0.90f);
        }
        else {
            m_view.zoom(1.10f);
        }
    }
}