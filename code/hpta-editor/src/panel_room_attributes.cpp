#include "hpta-editor/panel_room_attributes.hpp"

#include "hpta-editor/map.hpp"
#include "hpta-editor/settings.hpp"
#include "hpta-lib/persistency/persistency.hpp"
#include "hpta-lib/util/hpta_strings.hpp"

#include <cstring>
#include <fmt/core.h>
#include <imgui.h>
#include <map>
#include <memory>

namespace {
struct UI_exit {
	char direction[50];
	char description[255];
	char room_id[255];
};

struct UI_item {
	int  quantity;
	char id[255];
};

struct UI_room {
	char id[255];
	char name[255];
	char description[1024];
};

struct UI_detail {
	char name[255];
	char description[1024];
};

static UI_room                g_room;
static std::vector<UI_exit>   g_exits;
static std::vector<UI_item>   g_items;
static std::vector<UI_detail> g_details;

} // namespace

void Panel_room_attributes::save_room()
{
	Room room(g_room.id);

	room.set_name(g_room.name);
	room.set_description(Hpta_strings::remove_newlines(g_room.description));

	std::vector<Room::Exit> exits;
	for (const auto &exit : g_exits) {
		exits.emplace_back(Room::Exit{exit.direction, exit.description, exit.room_id});
	}
	room.set_exits(exits);

	for (const auto &item : g_items) {
		room.add_item({item.quantity, Item{item.id}});
	}

	std::vector<Room::Detail> details;
	for (const auto &detail : g_details) {
		details.emplace_back(Room::Detail{detail.name, detail.description});
	}
	room.set_details(details);

	persistency::save_room(Hpta_config::get_string(Settings::gamedata_dir), room);

	m_event_engine.publish({Event::Type::ROOM_CHANGED});
}

void Panel_room_attributes::show_exit_tab_content()
{

	ImGui::BeginTable("Directions", 4, ImGuiTableFlags_Resizable + ImGuiTableFlags_Borders);

	ImGui::TableSetupColumn("Action##directions");
	ImGui::TableSetupColumn("Direction##directions");
	ImGui::TableSetupColumn("Description##directions");
	ImGui::TableSetupColumn("Room##directions");

	ImGui::TableHeadersRow();

	int i = 0;
	for (auto itr = g_exits.begin(); itr != g_exits.end(); ++itr) {
		ImGui::PushID(itr->direction);

		ImGui::TableNextColumn();
		ImGui::PushItemWidth(-1);
		const auto delete_pressed = ImGui::Button("Delete");
		ImGui::PopItemWidth();

		if (delete_pressed) {
			g_exits.erase(itr);
		}
		else {

			ImGui::TableNextColumn();
			ImGui::PushItemWidth(-1);
			ImGui::InputText("##direction", itr->direction, std::size(itr->direction));
			ImGui::PopItemWidth();

			ImGui::TableNextColumn();
			ImGui::PushItemWidth(-1);
			ImGui::InputText("##description", itr->description, std::size(itr->description));
			ImGui::PopItemWidth();

			ImGui::TableNextColumn();
			ImGui::PushItemWidth(-1);
			ImGui::InputText("##room_id", itr->room_id, std::size(itr->room_id));
			ImGui::PopItemWidth();

			if (ImGui::BeginDragDropTarget()) {
				ImGuiDragDropFlags target_flags = 0;

				target_flags |= ImGuiDragDropFlags_AcceptNoDrawDefaultRect; // Don't display the yellow rectangle
				if (const ImGuiPayload *payload = ImGui::AcceptDragDropPayload("ROOM_ID", target_flags)) {
					strncpy(itr->room_id, static_cast<const char *>(payload->Data), std::size(itr->room_id));
				}
				ImGui::EndDragDropTarget();
			}
		}

		ImGui::PopID();

		ImGui::TableNextRow();
		++i;
	}

	ImGui::EndTable();

	if (ImGui::Button("Add Exit")) {
		UI_exit exit{"", "", ""};

		g_exits.emplace_back(exit);
	}
}

void Panel_room_attributes::show_item_tab_content()
{

	ImGui::BeginTable("Items", 3,
	                  ImGuiTableFlags_Resizable + ImGuiTableFlags_Borders); //

	ImGui::TableSetupColumn("Action");
	ImGui::TableSetupColumn("Quantity");
	ImGui::TableSetupColumn("Item");

	ImGui::TableHeadersRow();

	int i = 0;
	for (auto itr = g_items.begin(); itr != g_items.end(); ++itr) {
		ImGui::PushID(itr->id);

		ImGui::TableNextColumn();
		ImGui::PushItemWidth(-1);
		const auto delete_pressed = ImGui::Button(fmt::format("Delete##{}", itr->id).c_str());
		ImGui::PopItemWidth();

		if (delete_pressed) {
			g_items.erase(itr);
		}
		else {

			ImGui::TableNextColumn();
			ImGui::PushItemWidth(-1);
			ImGui::InputInt("##quantity", &itr->quantity);
			ImGui::PopItemWidth();

			ImGui::TableNextColumn();
			ImGui::PushItemWidth(-1);
			ImGui::InputText("##item", itr->id, std::size(itr->id));
			ImGui::PopItemWidth();
		}

		ImGui::PopID();

		ImGui::TableNextRow();
		++i;
	}

	ImGui::EndTable();

	if (ImGui::Button("Add Item")) {
		UI_item item{0, ""};

		g_items.emplace_back(item);
	}
}

void Panel_room_attributes::show_detail_tab_content()
{
	ImGui::BeginTable("Details", 3,
	                  ImGuiTableFlags_Resizable + ImGuiTableFlags_Borders); //

	ImGui::TableSetupColumn("Action");
	ImGui::TableSetupColumn("Name");
	ImGui::TableSetupColumn("Description");

	ImGui::TableHeadersRow();

	int i = 0;
	for (auto itr = g_details.begin(); itr != g_details.end(); ++itr) {
		ImGui::PushID(itr->name);

		ImGui::TableNextColumn();
		ImGui::PushItemWidth(-1);
		const auto delete_pressed = ImGui::Button(fmt::format("Delete##{}", itr->name).c_str());
		ImGui::PopItemWidth();

		if (delete_pressed) {
			g_details.erase(itr);
		}
		else {

			ImGui::TableNextColumn();
			ImGui::PushItemWidth(-1);
			ImGui::InputText("##name", itr->name, std::size(itr->name));
			ImGui::PopItemWidth();

			ImGui::TableNextColumn();
			ImGui::PushItemWidth(-1);
			ImGui::InputText("##item", itr->description, std::size(itr->description));
			ImGui::PopItemWidth();
		}

		ImGui::PopID();

		ImGui::TableNextRow();
		++i;
	}

	ImGui::EndTable();

	if (ImGui::Button("Add Detail")) {
		UI_detail detail{"", ""};

		g_details.emplace_back(detail);
	}
}

void Panel_room_attributes::set_room(const std::string &room_id)
{
	auto room = persistency::load_room(Hpta_config::get_string(Settings::gamedata_dir), room_id);

	set_room(room);
}

void Panel_room_attributes::set_room(Room &room)
{
	strncpy(g_room.id, room.get_id().c_str(), std::size(g_room.id) - 1);
	strncpy(g_room.name, room.get_name().c_str(), std::size(g_room.name) - 1);
	strncpy(g_room.description, Hpta_strings::add_newline_on_column_width(room.get_description(), 80).c_str(),
	        std::size(g_room.description) - 1);

	g_exits.clear();

	for (const auto &e : room.get_exits()) {
		UI_exit exit;

		strncpy(exit.direction, e.direction.c_str(), std::size(exit.direction) - 1);
		strncpy(exit.description, e.description.c_str(), std::size(exit.description) - 1);
		strncpy(exit.room_id, e.room_id.c_str(), std::size(exit.room_id) - 1);

		g_exits.emplace_back(exit);
	}

	g_items.clear();

	for (const auto &i : room.get_items()) {
		UI_item item;

		item.quantity = i.quantity;
		strncpy(item.id, i.item.get_id().c_str(), std::size(item.id) - 1);

		g_items.emplace_back(item);
	}

	g_details.clear();

	for (const auto &d : room.get_details()) {
		UI_detail detail;

		strncpy(detail.name, d.name.c_str(), std::size(detail.name) - 1);
		strncpy(detail.description, d.description.c_str(), std::size(detail.description) - 1);

		g_details.emplace_back(detail);
	}
}

void Panel_room_attributes::refresh()
{
	ImGui::Begin("Room");

	if (ImGui::Button("Save")) {
		save_room();
	}

	ImGui::SetWindowFontScale(Hpta_config::get_float(Settings::scale_factor));

	ImGui::PushItemWidth(-ImGui::GetWindowWidth() * 0.20f);
	ImGui::InputText("ID", g_room.id, std::size(g_room.id));
	ImGui::InputText("Name", g_room.name, std::size(g_room.name));
	ImGui::InputTextMultiline("Description", g_room.description, std::size(g_room.description), ImVec2(0, 0));
	ImGui::PopItemWidth();

	ImGui::BeginTabBar("tabs");

	if (ImGui::BeginTabItem("Exits")) {
		show_exit_tab_content();
		ImGui::EndTabItem();
	}

	if (ImGui::BeginTabItem("Items")) {
		show_item_tab_content();
		ImGui::EndTabItem();
	}

	if (ImGui::BeginTabItem("Details")) {
		show_detail_tab_content();
		ImGui::EndTabItem();
	}

	ImGui::EndTabBar();

	ImGui::End();
}

void Panel_room_attributes::on_event(Event event)
{
	switch (event.event_type) {
	case Event::Type::ROOM_SELECTED: {
		set_room(event.room_id);
		break;
	}
	case Event::Type::CREATE_ROOM: {
		Room room("/rooms/my-new-room.json");
		set_room(room);
	}
	default:
		break;
	}
}
