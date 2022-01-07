#include "hpta-editor/panel_item_list.hpp"

#include <imgui.h>

#include <vector>

void Panel_item_list::refresh()
{
	ImGui::Begin("Item List");
	ImGui::SetWindowFontScale(m_scale_factor);

	if (ImGui::Button("Refresh")) {
		m_item_cache.refresh();
	}
	if (ImGui::Button("Add")) {
		// TODO: set item in Panel_item_attribues
		//		Room room{"new-item.json"};
		//		Panel_room_attributes::set_room(room);
	}

	ImGui::Separator();

	ImGui::BeginChild("Scrolling");

	for (auto &item : m_item_cache.get_list()) {
		if (ImGui::Button(item.get_id().c_str())) {
			// TODO: set item in Panel_item_attribues
			//			Panel_room_attributes::set_room(room.get_id());
		}
	}

	ImGui::EndChild();

	ImGui::End();
}
