#include <iostream>

#include "hpta-lib/interpreter.hpp"
#include "hpta-lib/objects/player.hpp"
#include "hpta-lib/persistency/item_persistency.hpp"
#include "hpta-lib/screen.hpp"
#include "hpta-lib/services/registry.hpp"
#include "hpta-lib/visualizer.hpp"

#include <docopt/docopt.h>

static const char USAGE[] =
    R"(Harry Potter Textadveture

    Usage:
      hpta-editor [--gamedata_dir=<path>]
      hpta-editor (-h | --help)
      hpta-editor --version

    Options:
      --gamedata_dir=<path>   Path to the gamedata dir [default: gamedata]
      -h --help               Show this screen.
)";

int main(int argc, char *argv[])
{
	// clang-format off
	Screen::print(R"(        _  _                     ___     _   _                          )" "\n");
	Screen::print(R"(       | || |__ _ _ _ _ _ _  _  | _ \___| |_| |_ ___ _ _                )" "\n");
	Screen::print(R"(       | __ / _` | '_| '_| || | |  _/ _ \  _|  _/ -_) '_|               )" "\n");
	Screen::print(R"(       |_||_\__,_|_| |_|  \_, | |_| \___/\__|\__\___|_|                 )" "\n");
	Screen::print(R"(          _     _____     |__/           _             _                )" "\n");
	Screen::print(R"(         /_\   |_   _|____ _| |_ __ _ __| |_ _____ _ _| |_ _  _ _ _ ___ )" "\n");
	Screen::print(R"(        / _ \    | |/ -_) \ /  _/ _` / _` \ V / -_) ' \  _| || | '_/ -_))" "\n");
	Screen::print(R"(       /_/ \_\   |_|\___/_\_\\__\__,_\__,_|\_/\___|_||_\__|\_,_|_| \___|)" "\n");
	Screen::print(R"(                                                                        )" "\n");
	// clang-format on

	std::map<std::string, docopt::value> args = docopt::docopt(USAGE, {argv + 1, argv + argc},
	                                                           true, // show help if requested
	                                                           "Harry Potter Textadventure v1.0"); // version string

	Registry::m_gamedata_dir = args.find("--gamedata_dir")->second.asString();

	Interpreter interpreter;

	auto player = std::make_shared<Player>("Harry", "/rooms/winkelgasse/zum_tropfenden_kessel.json");

	player->add_item({30, Item_persistency::load(Registry::m_gamedata_dir, "/items/knut.json")});

	Registry::get_gameengine().set_player(player);

	Visualizer::show(Registry::get_persistence().get_room(player->get_room_id()));

	while (1) {
		const auto input = Screen::ask_for("");
		interpreter.parse(input);
	}
}
