#include "hpta-editor/panel_room_list.hpp"

#include <imgui.h>

#include <filesystem>
#include <vector>

#include "hpta-editor/map.hpp"
#include "hpta-editor/panel_room_attributes.hpp"
#include "hpta-editor/settings.hpp"

void Panel_room_list::refresh()
{
	ImGui::Begin("Room List");
	ImGui::SetWindowFontScale(Hpta_config::get_float(Settings::scale_factor));

	if (ImGui::Button("Refresh")) {
		Map::init();
	}
	if (ImGui::Button("Add")) {
		Room room{"new-room.json"};
		Panel_room_attributes::set_room(room);
	}

	ImGui::Separator();

	ImGui::BeginChild("Scrolling");

	for (auto &room : m_room_cache.get_list()) {
		if (ImGui::Button(room.get_id().c_str())) {
			Panel_room_attributes::set_room(room.get_id());
		}
	}

	ImGui::EndChild();

	ImGui::End();
}
