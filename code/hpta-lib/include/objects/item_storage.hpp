#ifndef ITEM_STORAGE_HPP
#define ITEM_STORAGE_HPP

#include "objects/item.hpp"

#include <vector>

class Item_storage {

  public:
	struct Entry {
		int  quantity;
		Item item;
	};

  private:
	std::vector<Entry> m_items;

  private:
	auto find_entry(const Item &item);

  public:
	int add_item(const Entry &entry);
	int remove_item(const Entry &&entry);

	auto &get_items() const
	{
		return m_items;
	}
};

#endif // ITEM_STORAGE_HPP
