#include <fstream>
#include <iostream>
#include <string>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <docopt/docopt.h>
#include <imgui-SFML.h>
#include <imgui.h>
#include <spdlog/cfg/argv.h>
#include <spdlog/spdlog.h>

#include "hpta-editor/map.hpp"
#include "hpta-editor/panel_room_attributes.hpp"
#include "hpta-editor/panel_room_selector.hpp"
#include "hpta-editor/settings.hpp"

static const char USAGE[] =
    R"(Harry Potter Textadveture Editor

    Usage:
      hpta-editor [--gamedata_dir=<path>] [--scale=<factor>] [--loglevel=<level>] [--configfile=<path>]
      hpta-editor (-h | --help)
      hpta-editor --version

    Options:
      --gamedata_dir=<path>   Path to the gamedata dir [default: gamedata]
      --configfile=<path>     Path to the configfile [default: config/hpta-editor.conf]
      --scale=<factor>        Scale factor of the gui [default: 1.0]
      --loglevel=<level>      Level of the logger [default: info]
      -h --help               Show this screen.
)";

static void window_refresh_loop(sf::RenderWindow &window)
{
	Panel_room_selector::refresh();
	Panel_room_attributes::refresh();
	Map::refresh(window);
}

static void load_configuration(std::map<std::string, docopt::value> &args)
{
	Hpta_config::add(Settings::gamedata_dir, args.find("--gamedata_dir")->second.asString());
	Hpta_config::add(Settings::scale_factor, args.find("--scale")->second.asString());
	Hpta_config::add(Settings::configfile, args.find("--configfile")->second.asString());
	Hpta_config::add(Settings::loglevel, args.find("--loglevel")->second.asString());

	std::ifstream is(Hpta_config::get_string(Settings::configfile), std::ifstream::in);

	if (!is.is_open()) {
		throw std::runtime_error("could not open configfile: " + Hpta_config::get_string(Settings::configfile));
	}

	Hpta_config::load(is);
	is.close();
}

int main(int argc, char *argv[])
{
	bool has_focus = true;

	spdlog::cfg::load_argv_levels(argc, argv);

	std::map<std::string, docopt::value> args =
	    docopt::docopt(USAGE, {argv + 1, argv + argc},
	                   true,                                      // show help if requested
	                   "Harry Potter Textadventure Editor v1.0"); // version string

	load_configuration(args);

	spdlog::info("editor is started!"); // print this always, independed of existing loglevel
	spdlog::set_level(spdlog::level::from_str(Hpta_config::get_string(Settings::loglevel)));

	Map::init();

	sf::View view;
	view.setCenter(sf::Vector2f(500.f, 500.f));
	view.setSize(sf::Vector2f(800.f, 600.f));

	view.setViewport(sf::FloatRect(0.f, 0.f, 0.8f, 1.f));

	const auto editor_window_width  = Hpta_config::get_uint(Settings::editor_width);
	const auto editor_window_height = Hpta_config::get_uint(Settings::editor_height);

	sf::RenderWindow window(sf::VideoMode(editor_window_width, editor_window_height),
	                        "Editor - Harry Potter Textadventure");

	window.setVerticalSyncEnabled(true);
	ImGui::SFML::Init(window);

	window.resetGLStates(); // call it if you only draw ImGui. Otherwise not needed.

	sf::Clock deltaClock;
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			ImGui::SFML::ProcessEvent(event);

			if (event.type == sf::Event::Closed) {
				window.close();
			}
			else if (event.type == sf::Event::GainedFocus) {
				has_focus = true;
			}
			else if (event.type == sf::Event::LostFocus) {
				has_focus = false;
			}
		}

		ImGui::SFML::Update(window, deltaClock.restart());
		window.clear();

		window_refresh_loop(window);

		if (has_focus) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
				view.move(-10.f, 0.f);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
				view.move(10.f, 0.f);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
				view.move(0.f, -10.f);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
				view.move(0.f, 10.f);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
				view.zoom(0.95f);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
				view.zoom(1.05f);
			}
		}

		window.setView(view);
		ImGui::SFML::Render(window);
		window.display();
	}

	ImGui::SFML::Shutdown();

	return 0;
}
