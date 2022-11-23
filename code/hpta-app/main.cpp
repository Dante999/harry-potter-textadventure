#include <iostream>

#include "hpta-lib/interpreter.hpp"
#include "hpta-lib/objects/player.hpp"
#include "hpta-lib/persistency/persistency.hpp"
#include "hpta-lib/screen/screen_terminal.hpp"
#include "hpta-lib/util/hpta_config.hpp"
#include "hpta-lib/visualizer.hpp"

#include "hpta-lib/services/player_walk_service.hpp"
#include "hpta-lib/services/room_cache_service.hpp"
#include "hpta-lib/services/service_registry.hpp"
#include "hpta-lib/services/user_interaction_service.hpp"

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
    std::shared_ptr<IScreen> screen = std::make_shared<Screen_Terminal>();

    screen->println(R"(        _  _                     ___     _   _                          )");
    screen->println(R"(       | || |__ _ _ _ _ _ _  _  | _ \___| |_| |_ ___ _ _                )");
    screen->println(R"(       | __ / _` | '_| '_| || | |  _/ _ \  _|  _/ -_) '_|               )");
    screen->println(R"(       |_||_\__,_|_| |_|  \_, | |_| \___/\__|\__\___|_|                 )");
    screen->println(R"(          _     _____     |__/           _             _                )");
    screen->println(R"(         /_\   |_   _|____ _| |_ __ _ __| |_ _____ _ _| |_ _  _ _ _ ___ )");
    screen->println(R"(        / _ \    | |/ -_) \ /  _/ _` / _` \ V / -_) ' \  _| || | '_/ -_))");
    screen->println(R"(       /_/ \_\   |_|\___/_\_\\__\__,_\__,_|\_/\___|_||_\__|\_,_|_| \___|)");
    screen->println(R"(                                                                        )");

    std::map<std::string, docopt::value> args = docopt::docopt(USAGE, {argv + 1, argv + argc},
                                                               true, // show help if requested
                                                               "Harry Potter Textadventure v1.0"); // version string

    const auto gamedata_dir = args.find("--gamedata_dir")->second.asString();

    Interpreter interpreter;

    auto player = std::make_shared<Player>("Harry", "/rooms/winkelgasse/zum_tropfenden_kessel.json");

    player->add_item({30, persistency::load_item(gamedata_dir, "/items/knut.json")});
    player->add_item({1, persistency::load_item(gamedata_dir, "/items/eulenfeder.json")});

    Service_registry service_registry;
    service_registry.add(std::make_shared<Room_cache_service>(gamedata_dir));
    service_registry.add(std::make_shared<Player_walk_service>(service_registry, player));
    service_registry.add(std::make_shared<User_Interaction_Service>(screen));

    const auto visualizer = service_registry.get<User_Interaction_Service>()->get_visualizer();

    visualizer->show(service_registry.get<Room_cache_service>()->get_room(player->get_room_id()));

    Context context{player, service_registry, gamedata_dir};

    while (1) {
        const auto input = screen->ask_for("");
        interpreter.parse(context, input);
    }
}
