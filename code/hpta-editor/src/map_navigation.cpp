#include "hpta-editor/map_navigation.hpp"

#include <SFML/Window/Mouse.hpp>
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
