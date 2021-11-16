#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <memory>

#include "../directions.hpp"
#include "../objects/player.hpp"

class Gameengine {
  private:
	std::shared_ptr<Player> m_player;

  public:
	bool walk(const Direction &direction);

	void set_player(const std::shared_ptr<Player> &player)
	{
		m_player = player;
	}

	[[nodiscard]] std::shared_ptr<Player> &get_player()
	{
		return m_player;
	}
};

#endif /* GAMEENGINE_H */
