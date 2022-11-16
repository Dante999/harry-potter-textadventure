#include "window_spells.hpp"

#include "utils.hpp"

namespace {
struct UI_Spell {
    char id[255];
    char name[255];
    char description[1024];
};

UI_Spell g_spell{};
} // namespace

void Window_Spells::create_object() {
    m_current_object = Spell{"/spells/unknown.json"};

    m_current_object.set_name("no name");
    m_current_object.set_description("no description");
    m_current_index = -1;

    load_object(m_current_object);
}

void Window_Spells::load_object(const Spell &spell)
{

    strncpy(g_spell.id, spell.get_id().c_str(), sizeof(g_spell.id) - 1);
    strncpy(g_spell.name, spell.get_name().c_str(), sizeof(g_spell.name) - 1);
    strncpy(g_spell.description, utils::wrap_text(spell.get_description()).c_str(), sizeof(g_spell.description) - 1);
}

std::vector<Spell> Window_Spells::get_objects() { return m_spell_cache.get_list(); }

void Window_Spells::refresh_cache() { m_spell_cache.refresh(); }

void Window_Spells::save_object() {
    Spell spell(g_spell.id);

    spell.set_name(g_spell.name);
    spell.set_description(Hpta_strings::trim(Hpta_strings::remove_newlines(g_spell.description)));

    persistency::save_spell(Hpta_config::get_string(Settings::gamedata_dir), spell);
    refresh_cache();
}

void Window_Spells::show_attributes()
{
    ImGui::PushItemWidth(-ImGui::GetWindowWidth() * 0.20f);
    ImGui::InputText("ID", g_spell.id, std::size(g_spell.id));
    ImGui::InputText("Name", g_spell.name, std::size(g_spell.name));
    utils::InputTextMultilineWrapped("Description", g_spell.description, std::size(g_spell.description));
    ImGui::PopItemWidth();
}