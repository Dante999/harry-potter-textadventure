#include "panel_room_attributes.hpp"

#include "persistency/room_persistency.hpp"
#include "settings.hpp"
#include "util/hpta_strings.hpp"

#include <cstring>
#include <fmt/core.h>
#include <imgui.h>
#include <map>
#include <memory>

namespace {
struct Exit {
	char direction[50];
	char description[255];
	char room_id[255];
};

char g_room_id[255];
char g_room_name[255];
char g_room_description[1024];

static std::vector<Exit> g_exits;

} // namespace

namespace Panel_room_attributes {

static void save_room()
{
	Room room(g_room_id);

	room.set_name(g_room_name);
	room.set_description(Hpta_strings::remove_newlines(g_room_description));

	std::vector<Room::Exit> exits;

	for (const auto &exit : g_exits) {
		exits.emplace_back(Room::Exit{exit.direction, exit.description, exit.room_id});
	}

	room.set_exits(exits);

	Room_persistency::save(Settings::gamedata_dir, room);
}

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

		strncpy(exit.direction, e.direction.c_str(), std::size(exit.direction) - 1);
		strncpy(exit.description, e.description.c_str(), std::size(exit.description) - 1);
		strncpy(exit.room_id, e.room_id.c_str(), std::size(exit.room_id) - 1);

		g_exits.emplace_back(exit);
	}
}

void refresh()
{
	ImGui::Begin("Room");
	ImGui::SetWindowFontScale(Settings::scale_factor);

	ImGui::InputText("ID", g_room_id, std::size(g_room_id));
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

	int i = 0;
	for (auto itr = g_exits.begin(); itr != g_exits.end(); ++itr) {

		ImGui::PushID(itr->direction);

		ImGui::TableNextColumn();

		if (ImGui::Button(fmt::format("Delete##{}", itr->direction).c_str())) {
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

		ImGui::TableNextRow();
		++i;

		ImGui::PopID();
	}

	ImGui::EndTable();

	if (ImGui::Button("Add Exit")) {
		Exit exit{"", "", ""};

		g_exits.emplace_back(exit);
	}

	if (ImGui::Button("Save")) {
		save_room();
	}

	ImGui::End();
}

} // namespace Panel_room_attributes
