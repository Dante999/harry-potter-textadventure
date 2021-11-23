#include "objects/item_storage.hpp"

#include <algorithm>

auto Item_storage::find_entry(Item &item)
{
	return std::find_if(m_items.begin(), m_items.end(), [&item](auto &i) { return i.item.get_id() == item.get_id(); });
}

void Item_storage::add_item(Entry entry)
{

	if (auto existing_entry = find_entry(entry.item); existing_entry != m_items.end()) {
		existing_entry->quantity += entry.quantity;
	}
	else {
		m_items.emplace_back(entry);
	}
}

void Item_storage::remove_item(Entry entry)
{

	if (auto existing_entry = find_entry(entry.item); existing_entry != m_items.end()) {
		existing_entry->quantity -= entry.quantity;

		if (existing_entry->quantity <= 0) {
			m_items.erase(existing_entry);
		}
	}
}
