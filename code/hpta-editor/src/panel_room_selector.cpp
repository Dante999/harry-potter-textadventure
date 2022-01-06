#include "hpta-editor/panel_room_selector.hpp"

#include <imgui.h>

#include <filesystem>
#include <vector>

#include "hpta-editor/panel_room_attributes.hpp"
#include "hpta-editor/room_list.hpp"
#include "hpta-editor/settings.hpp"

namespace Panel_room_selector {

void refresh()
{
	ImGui::Begin("Room List");
	ImGui::SetWindowFontScale(Hpta_config::get_float(Settings::scale_factor));

	if (ImGui::Button("Refresh")) {
		Room_list::refresh_rooms();
	}

	ImGui::Separator();

	ImGui::BeginChild("Scrolling");

	for (auto &room : Room_list::get_rooms()) {
		if (ImGui::Button(room.get_id().c_str())) {
			Panel_room_attributes::set_room(room.get_id());
		}
	}

	ImGui::EndChild();

	ImGui::End();
}
} // namespace Panel_room_selector
