#include "hpta-editor/panel_item_attributes.hpp"

#include "hpta-editor/settings.hpp"
#include "hpta-lib/persistency/item_persistency.hpp"
#include "hpta-lib/util/hpta_strings.hpp"

#include <cstring>
#include <fmt/core.h>
#include <imgui.h>
#include <map>
#include <memory>

namespace {

struct UI_item {
	char id[255];
	char name[255];
	char description[1024];
};

static UI_item g_item;

} // namespace

void Panel_item_attributes::save_room()
{
	Item item(g_item.id);

	item.set_name(g_item.name);
	item.set_description(Hpta_strings::remove_newlines(g_item.description));

	Item_persistency::save(Hpta_config::get_string(Settings::gamedata_dir), item);

	m_event_engine.publish({Event::Type::ITEM_CHANGED});
}

void Panel_item_attributes::set_item(const std::string &item_id)
{
	auto item = Item_persistency::load(Hpta_config::get_string(Settings::gamedata_dir), item_id);

	set_item(item);
}

void Panel_item_attributes::set_item(Item &item)
{
	strncpy(g_item.id, item.get_id().c_str(), std::size(g_item.id) - 1);
	strncpy(g_item.name, item.get_name().c_str(), std::size(g_item.name) - 1);
	strncpy(g_item.description, Hpta_strings::add_newline_on_column_width(item.get_description(), 80).c_str(),
	        std::size(g_item.description) - 1);
}

void Panel_item_attributes::refresh()
{
	ImGui::Begin("Item");

	if (ImGui::Button("Save")) {
		save_room();
	}

	ImGui::SetWindowFontScale(Hpta_config::get_float(Settings::scale_factor));

	ImGui::PushItemWidth(-ImGui::GetWindowWidth() * 0.20f);
	ImGui::InputText("ID", g_item.id, std::size(g_item.id));
	ImGui::InputText("Name", g_item.name, std::size(g_item.name));
	ImGui::InputTextMultiline("Description", g_item.description, std::size(g_item.description), ImVec2(0, 0));
	ImGui::PopItemWidth();

	ImGui::End();
}

void Panel_item_attributes::on_event(Event event)
{
	switch (event.event_type) {
	case Event::Type::ITEM_SELECTED: {
		set_item(event.item_id);
		break;
	}
	case Event::Type::CREATE_ROOM: {
		Item item{"/items/my-new-item.json"};
		set_item(item);
	}
	default:
		break;
	}
}
