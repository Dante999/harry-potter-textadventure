#include "panel_room_list.hpp"

#include <imgui.h>

#include <filesystem>
#include <vector>

#include "settings.hpp"

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

        ImGuiDragDropFlags src_flags = 0;
        src_flags |= ImGuiDragDropFlags_SourceNoDisableHover; // Keep the source displayed as hovered
        src_flags |= ImGuiDragDropFlags_SourceNoHoldToOpenOthers;

        if (ImGui::BeginDragDropSource(src_flags)) {

            if (!(src_flags & ImGuiDragDropFlags_SourceNoPreviewTooltip)) {
                ImGui::Text("Moving \"%s\"", room.get_id().c_str());
            }

            ImGui::SetDragDropPayload("ROOM_ID", room.get_id().c_str(), strlen(room.get_id().c_str()) + 1);
            ImGui::EndDragDropSource();
        }
    }

    ImGui::EndChild();

    ImGui::End();
}
