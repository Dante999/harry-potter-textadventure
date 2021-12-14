#ifndef PLAYER_H
#define PLAYER_H

#include <string>

#include "hpta-lib/objects/item_storage.hpp"

class Player : public Item_storage {

  private:
	std::string m_name;
	std::string m_room_id;

	uint8_t m_strength = 10;
	uint8_t m_dextery  = 10;
	uint8_t m_vitality = 10;
	uint8_t m_magic    = 10;

	uint16_t m_life_points = 50;
	uint16_t m_mana_points = 50;

  public:
	Player(const std::string &name, const std::string &room_id) : m_name(name), m_room_id(room_id) {}

	void set_room_id(const std::string &room_id)
	{
		m_room_id = room_id;
	}

	[[nodiscard]] auto get_name() const
	{
		return m_name;
	}
	[[nodiscard]] auto get_strength() const
	{
		return m_strength;
	}
	[[nodiscard]] auto get_dextery() const
	{
		return m_dextery;
	}
	[[nodiscard]] auto get_vitality() const
	{
		return m_vitality;
	}
	[[nodiscard]] auto get_magic() const
	{
		return m_magic;
	}
	[[nodiscard]] auto get_life_points() const
	{
		return m_life_points;
	}
	[[nodiscard]] auto get_mana_points() const
	{
		return m_mana_points;
	}
	[[nodiscard]] auto get_room_id() const
	{
		return m_room_id;
	}
};

#endif /* PLAYER_H */
