#include "panel_room_attributes.hpp"

#include "persistency/room_persistency.hpp"
#include "util/hpta_strings.hpp"

#include <cstring>
#include <imgui.h>

namespace {
char g_room_id[255];
char g_room_name[255];
char g_room_description[1024];

std::string g_gamedata_dir = "gamedata";
} // namespace

namespace Panel_room_attributes {

void set_room(const std::string &room_id)
{
	auto room = Room_persistency::load(g_gamedata_dir, room_id);

	strncpy(g_room_id, room_id.c_str(), std::size(g_room_id) - 1);
	strncpy(g_room_name, room.get_name().c_str(), std::size(g_room_name) - 1);
	strncpy(g_room_description, Hpta_strings::add_newline_on_column_width(room.get_description(), 80).c_str(),
	        std::size(g_room_description) - 1);
}

void refresh()
{
	ImGui::Begin("Room");

	ImGui::InputText("Name", g_room_name, std::size(g_room_name));
	ImGui::InputTextMultiline("Description", g_room_description, std::size(g_room_description), ImVec2(0, 0));

	if (ImGui::Button("Save")) {
		Room room(std::string(g_room_id) + ".new");

		room.set_name(g_room_name);
		room.set_description(Hpta_strings::remove_newlines(g_room_description));

		Room_persistency::save(g_gamedata_dir, room);
	}

	ImGui::End();
}

void set_gamedata_dir(const std::string &gamedata_dir)
{
	g_gamedata_dir = gamedata_dir;
}

} // namespace Panel_room_attributes
