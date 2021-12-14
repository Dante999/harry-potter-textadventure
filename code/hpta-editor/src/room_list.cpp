#include "room_list.hpp"

#include <filesystem>
#include <vector>

#include "hpta-lib/persistency/room_persistency.hpp"
#include "settings.hpp"

namespace Room_list {

static std::vector<Room> m_rooms;

void refresh_rooms()
{
	m_rooms.clear();

	for (const auto &file : std::filesystem::recursive_directory_iterator(Settings::gamedata_dir + "/rooms")) {

		if (file.is_directory())
			continue;

		const auto room_id = file.path().string().substr(Settings::gamedata_dir.length());

		m_rooms.emplace_back(Room_persistency::load(Settings::gamedata_dir, room_id));
	}
}

std::vector<Room> get_rooms()
{
	return m_rooms;
}

} // namespace Room_list
