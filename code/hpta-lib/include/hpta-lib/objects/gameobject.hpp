#ifndef ORGANISM_HPP
#define ORGANISM_HPP

#include <string>

class Gameobject {
  private:
	std::string m_id;
	std::string m_description;
	std::string m_name;
	

  public:
	Gameobject(const std::string &id) : m_id{id} {}

	// clang-format off
	[[nodiscard]] auto get_id() const {return m_id;}
	[[nodiscard]] auto get_name() const {return m_name;}
	[[nodiscard]] auto get_description() const {return m_description;}

	void set_name(const std::string &name) {m_name = name;}
	void set_description(const std::string &description) {m_description = description;}
	
	// clang-format on
};

#endif /* ORGANISM_HPP */
