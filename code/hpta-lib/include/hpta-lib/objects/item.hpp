#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>

class Item {
  private:
	std::string m_id;
	std::string m_name;
	std::string m_description;

  public:
	// clang-format off
	explicit Item(const std::string& id) : m_id(id) {}

	void set_name(const std::string& name) {m_name = name;}
	void set_description(const std::string& description) {m_description = description;}

	[[nodiscard]] auto& get_id() const {return m_id;}
	[[nodiscard]] auto& get_name() const {return m_name;}
	[[nodiscard]] auto& get_description() const {return m_description;}

	// clang-format on
};

#endif // ITEM_HPP
