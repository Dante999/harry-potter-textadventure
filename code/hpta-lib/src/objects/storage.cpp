#include "hpta-lib/objects/storage.hpp"

#include <algorithm>
#include <iterator>

auto Storage::find_entry(const Item &item)
{
	return std::find_if(m_items.begin(), m_items.end(), [&item](auto &i) { return i.item.get_id() == item.get_id(); });
}

int Storage::add_item(const Entry &entry)
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

int Storage::remove_item(const Storage::Entry &&entry)
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
