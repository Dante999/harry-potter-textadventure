#include "panel_spells.hpp"

#include <imgui.h>

#include <filesystem>
#include <vector>

#include "hpta-lib/util/hpta_strings.hpp"
#include "settings.hpp"
#include "utils.hpp"

namespace {
struct UI_Spell {
    char id[255];
    char name[255];
    char description[1024];
};

UI_Spell g_spell{};

int g_selected_spell = -1;
} // namespace

void Panel_Spells::load_spell_attributes(const Spell &spell)
{
    strncpy(g_spell.id, spell.get_id().c_str(), sizeof(g_spell.id));
    strncpy(g_spell.name, spell.get_name().c_str(), sizeof(g_spell.name));

    auto description_wrapped = Hpta_strings::add_newline_on_column_width(spell.get_description(), 30);
    strncpy(g_spell.description, description_wrapped.c_str(), sizeof(g_spell.description) - 1);
}

void Panel_Spells::save_spell_attributes(Spell &spell) { spell.set_name(std::string(g_spell.name)); }

void Panel_Spells::show_spell_list()
{

    auto spells = m_spell_cache.get_list();

    size_t longest_spell = 0;

    for (const auto &s : spells) {
        if (s.get_name().length() > longest_spell) {
            longest_spell = s.get_name().length();
        }
    }
    static int selected_old = -1;

    for (int i = 0; i < static_cast<int>(spells.size()); i++) {
        if (ImGui::Selectable(spells.at(static_cast<size_t>(i)).get_id().c_str(), g_selected_spell == i))
            if (selected_old != i) {
                g_selected_spell = i;
                selected_old     = i;
                load_spell_attributes(spells.at(static_cast<size_t>(i)));
            }
    }
}

void Panel_Spells::show_spell_attributes()
{

    // ImGui::BeginGroup();

    // ImGui::BeginChild("item view", ImVec2(0, -ImGui::GetFrameHeightWithSpacing())); // Leave room for 1 line below us
    //  ImGui::BeginChild("spell attributes", ImVec2(0, 0), true);
    // ImGui::PushItemWidth(-ImGui::GetWindowWidth() * 0.20f);
    ImGui::InputText("ID", g_spell.id, std::size(g_spell.id));
    ImGui::InputText("Name", g_spell.name, std::size(g_spell.name));
    utils::InputTextMultilineWrapped("Description", g_spell.description, std::size(g_spell.description));

    // ImGui::PopItemWidth();
    //  ImGui::EndChild();

    // ImGui::EndGroup();
}

void Panel_Spells::refresh()
{
    ImGui::Begin("Panel Spells");
    ImGui::SetWindowFontScale(Hpta_config::get_float(Settings::scale_factor));

    if (ImGui::Button("Refresh")) {
        m_spell_cache.refresh();
        // m_event_engine.publish({Event::Type::ROOM_CHANGED});
    }

    ImGui::SameLine();
    if (ImGui::Button("Add")) {
        // m_event_engine.publish({Event::Type::CREATE_ROOM});
    }

    ImGui::SameLine();
    if (ImGui::Button("Save")) {
        // save_room();
    }

    ImGui::Separator();

    ImGui::BeginTable("spells_table", 2, ImGuiTableFlags_Resizable | ImGuiTableFlags_Borders, ImVec2(0.0f, -1.0f),
                      -1.0f);
    ImGui::TableNextColumn();
    ImGui::PushItemWidth(-1);
    show_spell_list();
    ImGui::PopItemWidth();
    ImGui::TableNextColumn();
    show_spell_attributes();
    ImGui::EndTable();

    ImGui::End();
}
