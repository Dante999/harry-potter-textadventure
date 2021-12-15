#include "hpta-editor/room_list.hpp"

#include <filesystem>
#include <vector>

#include <spdlog/spdlog.h>

#include "hpta-editor/settings.hpp"
#include "hpta-lib/persistency/room_persistency.hpp"

namespace Room_list {

static std::vector<Room> m_rooms;

void refresh_rooms()
{
	m_rooms.clear();

	for (const auto &file : std::filesystem::recursive_directory_iterator(Settings::gamedata_dir + "/rooms")) {

		if (file.is_directory())
			continue;

		const auto room_id = file.path().string().substr(Settings::gamedata_dir.length());
		spdlog::info("loading room {}", room_id);

		m_rooms.emplace_back(Room_persistency::load(Settings::gamedata_dir, room_id));
	}
}

std::vector<Room> get_rooms()
{
	return m_rooms;
}

} // namespace Room_list
