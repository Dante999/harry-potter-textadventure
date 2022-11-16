#include "panel_item_list.hpp"

#include <imgui.h>

#include <vector>

void Panel_item_list::refresh()
{
    ImGui::Begin("Item List");
    ImGui::SetWindowFontScale(m_scale_factor);

    if (ImGui::Button("Refresh")) {
        m_item_cache.refresh();
        m_event_engine.publish({Event::Type::ITEM_CHANGED});
    }

    ImGui::SameLine();
    if (ImGui::Button("Add")) {
        m_event_engine.publish({Event::Type::CREATE_ITEM});
    }

    ImGui::Separator();

    ImGui::BeginChild("Scrolling");

    for (auto &item : m_item_cache.get_list()) {
        if (ImGui::Button(item.get_id().c_str())) {
            m_event_engine.publish({Event::Type::ITEM_SELECTED, "", item.get_id()});
        }
    }

    ImGui::EndChild();

    ImGui::End();
}
