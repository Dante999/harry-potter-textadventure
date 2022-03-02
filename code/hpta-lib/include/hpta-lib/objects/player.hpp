#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>

#include "hpta-lib/objects/storage.hpp"
#include "hpta-lib/objects/gameobject.hpp"

class Player : public Storage, public Gameobject {

  private:
	uint8_t m_strength = 10;
	uint8_t m_dextery  = 10;
	uint8_t m_vitality = 10;
	uint8_t m_magic    = 10;

	uint16_t m_life_points = 50;
	uint16_t m_mana_points = 50;
	std::string m_room_id;

  public:
	Player(const std::string &name, const std::string &room_id) : Gameobject{"player"}, m_room_id{room_id} {
		set_name(name);
	}

	// clang-format off
	void set_room_id(const std::string &room_id) {m_room_id = room_id;}

	[[nodiscard]] auto get_room_id() const {return m_room_id;}
	[[nodiscard]] auto get_strength() const {return m_strength;}
	[[nodiscard]] auto get_dextery() const {return m_dextery;}
	[[nodiscard]] auto get_vitality() const {return m_vitality;}
	[[nodiscard]] auto get_magic() const {return m_magic;}
	[[nodiscard]] auto get_life_points() const {return m_life_points;}
	[[nodiscard]] auto get_mana_points() const {return m_mana_points;}

	// clang-format on
};

#endif /* PLAYER_HPP */
