#include "panel_room_selector.hpp"

#include <imgui.h>

#include <filesystem>
#include <vector>

#include "panel_room_attributes.hpp"
#include "settings.hpp"

namespace {
std::vector<std::string> g_room_ids;
} // namespace

namespace Panel_room_selector {

void refresh_room_list(const std::string &gamedata_dir)
{
	g_room_ids.clear();

	for (const auto &file : std::filesystem::recursive_directory_iterator(Settings::gamedata_dir + "/rooms")) {

		if (file.is_directory())
			continue;

		const auto room_id = file.path().string().substr(gamedata_dir.length());
		g_room_ids.emplace_back(room_id);
	}
}

void refresh()
{
	ImGui::Begin("Room List");
	ImGui::SetWindowFontScale(Settings::scale_factor);

	if (ImGui::Button("Refresh")) {
		refresh_room_list(Settings::gamedata_dir);
	}

	ImGui::BeginChild("Scrolling");

	for (auto &room_id : g_room_ids) {
		if (ImGui::Button(room_id.c_str())) {
			Panel_room_attributes::set_room(room_id);
		}
	}

	ImGui::EndChild();

	ImGui::End();
}
} // namespace Panel_room_selector
