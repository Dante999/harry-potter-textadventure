#include <iostream>

#include "interpreter.hpp"
#include "objects/player.hpp"
#include "persistency/item_persistency.hpp"
#include "screen.hpp"
#include "services/registry.hpp"
#include "visualizer.hpp"

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

	if (argc == 2)
		Registry::m_gamedata_dir = argv[1];

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
