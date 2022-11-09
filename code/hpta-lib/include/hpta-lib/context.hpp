#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include "hpta-lib/objects/player.hpp"
#include "hpta-lib/screen/iscreen.hpp"
#include "hpta-lib/services/service_registry.hpp"
#include "hpta-lib/visualizer.hpp"

struct Context {
    std::shared_ptr<Player> player;
    Service_registry &      service_registry;
};

#endif /* CONTEXT_HPP */
