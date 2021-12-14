#include <string>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <imgui-SFML.h>
#include <imgui.h>
#include <spdlog/cfg/argv.h>
#include <spdlog/spdlog.h>

#include "hpta-editor/map.hpp"
#include "hpta-editor/panel_room_attributes.hpp"
#include "hpta-editor/panel_room_selector.hpp"
#include "hpta-editor/settings.hpp"

static void window_refresh_loop(sf::RenderWindow &window)
{
	//	Panel_room_selector::refresh();
	Panel_room_attributes::refresh();
	Map::refresh(window);
}

int main(int argc, char *argv[])
{
	spdlog::cfg::load_argv_levels(argc, argv);

	spdlog::info("hello world!");

	if (argc >= 3) {
		Settings::gamedata_dir = argv[1];
		Settings::scale_factor = std::stof(argv[2]);
	}
	else if (argc == 2) {
		Settings::gamedata_dir = argv[1];
	}

	Map::init();

	sf::RenderWindow window(sf::VideoMode(2500, 1500), "");
	window.setVerticalSyncEnabled(true);
	ImGui::SFML::Init(window);

	window.setTitle("Editor - Harry Potter Textadventure");
	window.resetGLStates(); // call it if you only draw ImGui. Otherwise not needed.

	sf::Clock deltaClock;
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			ImGui::SFML::ProcessEvent(event);

			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		ImGui::SFML::Update(window, deltaClock.restart());
		window.clear();

		window_refresh_loop(window);

		ImGui::SFML::Render(window);
		window.display();
	}

	ImGui::SFML::Shutdown();
}
