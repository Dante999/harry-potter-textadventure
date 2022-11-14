#ifndef WALK_SERVICE_HPP
#define WALK_SERVICE_HPP

#include <memory>

#include "hpta-lib/objects/player.hpp"
#include "hpta-lib/services/service_registry.hpp"

class Player_walk_service {
  private:
    Service_registry &      m_service_registry;
    std::shared_ptr<Player> m_player;

  public:
    Player_walk_service(Service_registry &service_registry, std::shared_ptr<Player> player)
        : m_service_registry{service_registry}, m_player{player}
    {
    }

    bool walk(const std::string &direction);

    [[nodiscard]] auto &get_player() { return m_player; }
};

#endif // WALK_SERVICE_HPP
