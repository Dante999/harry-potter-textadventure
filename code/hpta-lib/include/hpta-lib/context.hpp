#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include "hpta-lib/objects/player.hpp"
#include "hpta-lib/services/service_registry.hpp"

struct Context {
    std::shared_ptr<Player> player;
    Service_registry &      service_registry;
    const std::string       gamedata_dir;
};

#endif /* CONTEXT_HPP */
