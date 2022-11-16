#include "window_items.hpp"

#include "utils.hpp"

namespace {

struct UI_item {
    char id[255];
    char name[255];
    char description[1024];
};

static UI_item g_item;
} // namespace

void Window_Items::create_object() {}

void Window_Items::load_object(const Item &item)
{
    strncpy(g_item.id, item.get_id().c_str(), std::size(g_item.id) - 1);
    strncpy(g_item.name, item.get_name().c_str(), std::size(g_item.name) - 1);
    strncpy(g_item.description, utils::wrap_text(item.get_description()).c_str(), std::size(g_item.description) - 1);
}

std::vector<Item> Window_Items::get_objects() { return m_item_cache.get_list(); }

void Window_Items::refresh_cache() { m_item_cache.refresh(); }

void Window_Items::save_object() {}

void Window_Items::show_attributes()
{
    ImGui::PushItemWidth(-ImGui::GetWindowWidth() * 0.20f);
    ImGui::InputText("ID", g_item.id, std::size(g_item.id));
    ImGui::InputText("Name", g_item.name, std::size(g_item.name));
    utils::InputTextMultilineWrapped("Description", g_item.description, std::size(g_item.description), ImVec2(0, 0));
    ImGui::PopItemWidth();
}