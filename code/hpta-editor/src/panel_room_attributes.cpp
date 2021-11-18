#include "panel_room_attributes.hpp"

#include "directions.hpp"
#include "persistency/room_persistency.hpp"
#include "settings.hpp"
#include "util/hpta_strings.hpp"

#include <cstring>
#include <fmt/core.h>
#include <imgui.h>
#include <memory>

namespace {
struct Exit {
	int  direction_index;
	char direction[50];
	char description[255];
	char room_id[255];
};

char g_room_id[255];
char g_room_name[255];
char g_room_description[1024];

static std::vector<Exit> g_exits;

static std::vector<const char *> g_combobox_values = {"north", "south", "east", "west"};

} // namespace

namespace Panel_room_attributes {

static int combo_value_to_index(const char *value)
{

	for (size_t i = 0; i < g_combobox_values.size(); ++i) {
		if (strcmp(g_combobox_values.at(i), value) == 0) {
			return static_cast<int>(i);
		}
	}

	return 0;
}

// static const char *combo_index_to_value(int i)
//{
//	return g_combobox_values.at(i);
//}

void set_room(const std::string &room_id)
{
	auto room = Room_persistency::load(Settings::gamedata_dir, room_id);

	strncpy(g_room_id, room_id.c_str(), std::size(g_room_id) - 1);
	strncpy(g_room_name, room.get_name().c_str(), std::size(g_room_name) - 1);
	strncpy(g_room_description, Hpta_strings::add_newline_on_column_width(room.get_description(), 80).c_str(),
	        std::size(g_room_description) - 1);

	g_exits.clear();

	for (const auto &e : room.get_exits()) {
		Exit exit;

		strncpy(exit.direction, Room_persistency::serialize_direction(e.first).c_str(), std::size(exit.direction) - 1);
		strncpy(exit.description, e.second.description.c_str(), std::size(exit.description) - 1);
		strncpy(exit.room_id, e.second.room_id.c_str(), std::size(exit.room_id) - 1);
		g_exits.emplace_back(exit);
	}
}

void refresh()
{
	ImGui::Begin("Room");
	ImGui::SetWindowFontScale(Settings::scale_factor);
	ImGui::InputText("Name", g_room_name, std::size(g_room_name));
	ImGui::InputTextMultiline("Description", g_room_description, std::size(g_room_description), ImVec2(0, 0));

	ImGui::BeginTable("Directions", 4,
	                  ImGuiTableFlags_Resizable + ImGuiTableFlags_Borders); // static_cast<int>(g_exits.size()));

	ImGui::Spacing();

	ImGui::TableSetupColumn("Action");
	ImGui::TableSetupColumn("Direction");
	ImGui::TableSetupColumn("Description");
	ImGui::TableSetupColumn("Room");

	ImGui::TableHeadersRow();

	for (auto itr = g_exits.begin(); itr != g_exits.end(); ++itr) {

		ImGui::TableNextColumn();

		if (ImGui::Button(fmt::format("Delete##{}", itr->direction).c_str())) {
			g_exits.erase(itr);
		}
		else {

			ImGui::TableNextColumn();
			ImGui::PushItemWidth(-1);

			itr->direction_index = combo_value_to_index(itr->direction);

			ImGui::Combo(fmt::format("##Direction-{}", itr->direction).c_str(), &itr->direction_index,
			             g_combobox_values.data(), static_cast<int>(g_combobox_values.size()));

			ImGui::PopItemWidth();

			ImGui::TableNextColumn();
			ImGui::PushItemWidth(-1);
			ImGui::InputText(fmt::format("##Description-{}", itr->direction).c_str(), itr->description,
			                 std::size(itr->description));
			ImGui::PopItemWidth();

			ImGui::TableNextColumn();
			ImGui::PushItemWidth(-1);
			ImGui::InputText(fmt::format("##Room ID-{}", itr->direction).c_str(), itr->room_id,
			                 std::size(itr->room_id));
			ImGui::PopItemWidth();
		}

		ImGui::TableNextRow();
	}

	ImGui::EndTable();

	if (ImGui::Button("Save")) {
		Room room(std::string(g_room_id) + ".new");

		room.set_name(g_room_name);
		room.set_description(Hpta_strings::remove_newlines(g_room_description));

		Room_persistency::save(Settings::gamedata_dir, room);
	}

	ImGui::End();
}

} // namespace Panel_room_attributes
