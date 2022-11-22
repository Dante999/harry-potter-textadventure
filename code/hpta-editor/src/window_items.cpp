#include "window_items.hpp"

#include "utils.hpp"

#include "hpta_imgui.hpp"

namespace {

struct UI_item {
    std::string id;
    std::string name;
    std::string description;
};

static UI_item g_item;
} // namespace

std::vector<Item> Window_Items::get_objects() { return m_item_cache.get_list(); }

void Window_Items::refresh_cache() { m_item_cache.refresh(); }

void Window_Items::create_object()
{
    m_current_object = Item{"/items/unknown.json"};

    m_current_object.set_name("no name");
    m_current_object.set_description("no description");
}

void Window_Items::load_object()
{
    g_item.id          = m_current_object.get_id();
    g_item.name        = m_current_object.get_name();
    g_item.description = utils::wrap_text(m_current_object.get_description());
}

void Window_Items::save_object()
{
    m_current_object.set_id(g_item.id);
    m_current_object.set_name(g_item.name);
    m_current_object.set_description(Hpta_strings::trim(Hpta_strings::remove_newlines(g_item.description)));

    persistency::save_item(Hpta_config::get_string(Settings::gamedata_dir), m_current_object);
}

void Window_Items::show_attributes()
{
    ImGui::PushItemWidth(-ImGui::GetWindowWidth() * 0.20f);

    hpta_imgui::InputText("ID", g_item.id);
    hpta_imgui::InputText("Name", g_item.name);
    hpta_imgui::InputTextMultilineWrapped("Description", g_item.description);

    ImGui::PopItemWidth();
}