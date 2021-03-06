#include "hpta-lib/commands/take.hpp"

#include "hpta-lib/screen.hpp"
#include "hpta-lib/services/room_cache_service.hpp"
#include "hpta-lib/util/hpta_strings.hpp"

#include <algorithm>
#include <fmt/core.h>

bool Take::interprete(Context &context, const std::vector<std::string> &token)
{
	if (token.at(0) != "nimm")
		return false;

	if (token.size() < 3) {
		Screen::print("Was und wieviel soll ich nehmen?\n");
		return true;
	}

	const auto &str_quantity = token.at(1);
	if (str_quantity.back() != 'x') {
		Screen::print("Welche Anzahl soll ich nehmen?\n");
		return true;
	}

	int quantity = std::stoi(str_quantity.substr(0, str_quantity.length() - 1));

	std::string object_name;
	for (size_t i = 2; i < token.size(); ++i) {
		object_name += token.at(i) + " ";
	}

	auto &room = context.service_registry.get<Room_cache_service>()->get_room(context.player->get_room_id());

	const auto &storage_entries = room.get_items();

	const auto result = std::find_if(storage_entries.begin(), storage_entries.end(), [&object_name](auto &i) {
		return Hpta_strings::equals_ignorecase(i.item.get_name(), Hpta_strings::trim(object_name));
	});

	if (result == storage_entries.end()) {
		Screen::print("Diese Item finde ich nicht\n");
		return true;
	}

	// copy before removing it, otherwise you will get garbage
	Item item{result->item};

	const auto removed_quantity = room.remove_item({quantity, item});
	context.player->add_item({removed_quantity, item});

	Screen::print(fmt::format("{}x {} aufgenommen!\n\n", removed_quantity, item.get_name()));

	return true;
}
