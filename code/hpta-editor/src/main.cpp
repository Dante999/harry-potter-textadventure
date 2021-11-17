
#include <string>
#include <vector>

#include "persistency/room_persistency.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <imgui-SFML.h>
#include <imgui.h>

#include "panel_room_attributes.hpp"
#include "panel_room_selector.hpp"
#include "persistency/room_persistency.hpp"
#include "util/hpta_strings.hpp"

char g_room_id[255];
char g_room_name[255];
char g_room_description[1024];

std::vector<std::string> g_room_ids;

// static constexpr const char *g_gamedata_dir =
//    "/home/dante999/Projekte/pc-textadventure/2_Software/harry-potter-textadventure/gamedata";

// static void refresh_panel_room_details()
//{
//	ImGui::Begin("Room");

//	ImGui::InputText("Name", g_room_name, IM_ARRAYSIZE(g_room_name));
//	ImGui::InputTextMultiline("Description", g_room_description, IM_ARRAYSIZE(g_room_description), ImVec2(0, 0));

//	if (ImGui::Button("Save")) {
//		Room room(std::string(g_room_id) + ".new");

//		room.set_name(g_room_name);
//		room.set_description(Hpta_strings::remove_newlines(g_room_description));

//		Room_persistency::save(g_gamedata_dir, room);
//	}

//	ImGui::End();
//}

// static void refresh_current_room(const std::string &room_id)
//{
//	auto room = Room_persistency::load(g_gamedata_dir, room_id);

//	strncpy(g_room_id, room_id.c_str(), IM_ARRAYSIZE(g_room_id) - 1);
//	strncpy(g_room_name, room.get_name().c_str(), IM_ARRAYSIZE(g_room_name) - 1);
//	strncpy(g_room_description, Hpta_strings::add_newline_on_column_width(room.get_description(), 80).c_str(),
//	        IM_ARRAYSIZE(g_room_description) - 1);
//}

// void refresh_room_list(const std::string &gamedata_dir)
//{
//	g_room_ids.clear();

//	for (const auto &file : std::filesystem::recursive_directory_iterator(gamedata_dir + "/rooms")) {

//		if (file.is_directory())
//			continue;

//		const auto room_id = file.path().string().substr(gamedata_dir.length());
//		g_room_ids.emplace_back(room_id);
//	}
//}

// static void refresh_panel_room_navigator()
//{
//	ImGui::Begin("Room List");

//	if (ImGui::Button("Refresh")) {
//		refresh_room_list(g_gamedata_dir);
//	}

//	ImGui::BeginChild("Scrolling");

//	for (auto &room_id : g_room_ids) {
//		if (ImGui::Button(room_id.c_str())) {
//			Panel_room_attributes::set_room(room_id);
//		}
//	}

//	ImGui::EndChild();

//	ImGui::End();
//}

static void window_refresh_loop()
{
	Panel_room_selector::refresh();
	Panel_room_attributes::refresh();
}

int main(int argc, char *argv[])
{
	const std::string gamedata_dir = (argc == 2 ? (argv[1]) : "gamedata");

	Panel_room_attributes::set_gamedata_dir(gamedata_dir);
	Panel_room_selector::set_gamedata_dir(gamedata_dir);

	sf::RenderWindow window(sf::VideoMode(1280, 768), "");
	window.setVerticalSyncEnabled(true);
	ImGui::SFML::Init(window);

	window.setTitle("Editor - Harry Potter Textadventure");
	window.resetGLStates(); // call it if you only draw ImGui. Otherwise not needed.

	sf::Clock deltaClock;
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			ImGui::SFML::ProcessEvent(event);

			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		ImGui::SFML::Update(window, deltaClock.restart());

		window_refresh_loop();

		window.clear();
		ImGui::SFML::Render(window);
		window.display();
	}

	ImGui::SFML::Shutdown();
}
