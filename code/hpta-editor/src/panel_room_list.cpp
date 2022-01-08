#include "hpta-editor/panel_room_list.hpp"

#include <imgui.h>

#include <filesystem>
#include <vector>

#include "hpta-editor/settings.hpp"

void Panel_room_list::refresh()
{
	ImGui::Begin("Room List");
	ImGui::SetWindowFontScale(Hpta_config::get_float(Settings::scale_factor));

	if (ImGui::Button("Refresh")) {
		m_room_cache.refresh();
		m_event_engine.publish({Event::Type::ROOM_CHANGED});
	}

	ImGui::SameLine();
	if (ImGui::Button("Add")) {
		m_event_engine.publish({Event::Type::CREATE_ROOM});
	}

	ImGui::Separator();

	ImGui::BeginChild("Scrolling");

	for (auto &room : m_room_cache.get_list()) {
		if (ImGui::Button(room.get_id().c_str())) {
			m_event_engine.publish({Event::Type::ROOM_SELECTED, room.get_id()});
		}
	}

	ImGui::EndChild();

	ImGui::End();
}
