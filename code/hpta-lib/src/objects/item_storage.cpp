#include "objects/item_storage.hpp"

#include <algorithm>

auto Item_storage::find_entry(const Item &item)
{
	return std::find_if(m_items.begin(), m_items.end(), [&item](auto &i) { return i.item.get_id() == item.get_id(); });
}

int Item_storage::add_item(const Entry &entry)
{

	if (auto existing_entry = find_entry(entry.item); existing_entry != m_items.end()) {
		existing_entry->quantity += entry.quantity;
		return existing_entry->quantity;
	}
	else {
		m_items.emplace_back(entry);
		return entry.quantity;
	}
}

int Item_storage::remove_item(const Item_storage::Entry &&entry)
{

	int removed_quantity = 0;

	if (auto existing_entry = find_entry(entry.item); existing_entry != m_items.end()) {

		if (existing_entry->quantity <= entry.quantity) {
			removed_quantity = existing_entry->quantity;
			m_items.erase(existing_entry);
		}
		else {
			existing_entry->quantity -= entry.quantity;
			removed_quantity = entry.quantity;
		}
	}

	return removed_quantity;
}
