#include "panel_spells.hpp"

#include "hpta_imgui.hpp"
#include "utils.hpp"

namespace {
struct UI_Spell {
    std::string id;
    std::string name;
    std::string description;
    double level;
};

UI_Spell g_spell{};
} // namespace

std::vector<Spell> Panel_Spells::get_objects() { return m_world_cache.spells->get_list(); }

void Panel_Spells::refresh_cache() { m_world_cache.spells->refresh(); }

void Panel_Spells::create_object()
{
    m_current_object = Spell{"/spells/unknown.json"};

    m_current_object.set_name("no name");
    m_current_object.set_description("no description");
    m_current_object.set_level(1.0);
}

void Panel_Spells::load_object()
{
    g_spell.id          = m_current_object.get_id();
    g_spell.name        = m_current_object.get_name();
    g_spell.description = utils::wrap_text(m_current_object.get_description());
    g_spell.level       = m_current_object.get_level();
}

void Panel_Spells::save_object()
{
    m_current_object.set_id(g_spell.id);
    m_current_object.set_name(g_spell.name);
    m_current_object.set_description(Hpta_strings::trim(Hpta_strings::remove_newlines(g_spell.description)));
    m_current_object.set_level(g_spell.level);

    persistency::save_spell(Hpta_config::get_string(Settings::gamedata_dir), m_current_object);
}

void Panel_Spells::show_attributes()
{
    ImGui::PushItemWidth(hpta_imgui::get_textwrapwidth());

    hpta_imgui::InputText("ID", g_spell.id);
    hpta_imgui::InputText("Name", g_spell.name);
    hpta_imgui::InputTextMultilineWrapped("Description", g_spell.description);
    ImGui::InputDouble("Level", &g_spell.level, 1.0);

    ImGui::PopItemWidth();
}
