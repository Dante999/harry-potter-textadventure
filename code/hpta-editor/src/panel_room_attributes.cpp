#include "hpta-editor/panel_room_attributes.hpp"

#include "hpta-editor/map.hpp"
#include "hpta-editor/room_list.hpp"
#include "hpta-editor/settings.hpp"
#include "hpta-lib/persistency/room_persistency.hpp"
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

static UI_room              g_room;
static std::vector<UI_exit> g_exits;
static std::vector<UI_item> g_items;

} // namespace

namespace Panel_room_attributes {

static void save_room()
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

	Room_persistency::save(Hpta_config::get_string(Settings::gamedata_dir), room);

	Map::init();
}

static void show_exit_tab_content()
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

void show_item_tab_content()
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

void set_room(const std::string &room_id)
{
	auto room = Room_persistency::load(Hpta_config::get_string(Settings::gamedata_dir), room_id);

	set_room(room);
}

void set_room(Room &room)
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
}

void refresh()
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

	ImGui::EndTabBar();

	ImGui::End();
}

} // namespace Panel_room_attributes
