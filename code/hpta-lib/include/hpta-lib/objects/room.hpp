#ifndef ROOM_H
#define ROOM_H

#include <map>
#include <string>
#include <vector>

#include "hpta-lib/objects/item_storage.hpp"

class Room : public Item_storage {
  public:
	struct Exit {
		std::string direction;
		std::string description;
		std::string room_id;
	};

	struct Detail {
		std::string name;
		std::string description;
	};

  private:
	std::string         m_id;
	std::string         m_name;
	std::string         m_description;
	std::vector<Exit>   m_exits;
	std::vector<Detail> m_details;

  public:
	// clang-format off
	explicit Room(const std::string &id) : m_id(id) {}

	void set_id(const std::string &id) {m_id = id;}
	void set_name(const std::string &name) {m_name = name;}
	void set_description(const std::string &description) {m_description = description;}
	void set_exits(const std::vector<Exit> &exits) {m_exits = exits;}
	void set_details(const std::vector<Detail> &details) {m_details = details;}

	[[nodiscard]] auto get_id() const {return m_id;}
	[[nodiscard]] auto get_name() const {return m_name;}
	[[nodiscard]] auto get_description() const {return m_description;}
	[[nodiscard]] auto get_exits() const {return m_exits;}
	[[nodiscard]] auto get_details() const {return m_details;}
	// clang-format on
};

#endif /* ROOM_H */
