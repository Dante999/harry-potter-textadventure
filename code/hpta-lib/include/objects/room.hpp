#ifndef ROOM_H
#define ROOM_H

#include <map>
#include <string>

#include "../directions.hpp"

class Room {
  public:
	struct Branch {
		std::string description;
		std::string room_id;
	};

  private:
	std::string m_id;
	std::string m_name;
	std::string m_description;

	std::map<Direction, Branch> m_exits;

  public:
	explicit Room(const std::string &id) : m_id(id) {}

	void set_id(const std::string &id)
	{
		m_id = id;
	}
	void set_name(const std::string &name)
	{
		m_name = name;
	}
	void set_description(const std::string &description)
	{
		m_description = description;
	}
	void set_exits(const std::map<Direction, Branch> &exits)
	{
		m_exits = exits;
	}

	[[nodiscard]] auto get_id() const
	{
		return m_id;
	}
	[[nodiscard]] auto get_name() const
	{
		return m_name;
	}
	[[nodiscard]] auto get_description() const
	{
		return m_description;
	}
	[[nodiscard]] auto get_exits() const
	{
		return m_exits;
	}
};

#endif /* ROOM_H */
