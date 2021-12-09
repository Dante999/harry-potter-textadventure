#include "map.hpp"

#include <fmt/core.h>
#include <imgui-SFML.h>
#include <imgui.h>
#include <spdlog/spdlog.h>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

#include "objects/room.hpp"
#include "room_list.hpp"
#include "settings.hpp"
#include "util/hpta_strings.hpp"

static auto g_font = sf::Font();

struct Node;

struct Link {
	std::string direction;
	Node &      target;
};
struct Node {
	float             x;
	float             y;
	Room              room;
	std::vector<Link> links;
};

static std::vector<Node> g_nodes;

// static void draw_room(sf::RenderWindow &window, const std::string &id, float x, float y)
//{
//	auto text = sf::Text(id, g_font);
//	text.setPosition(x, y);
//	//	text.setScale(1.5, 1.5);

//	//	sf::RectangleShape shape({text.getGlobalBounds().width + 10, text.getGlobalBounds().height + 10});
//	//	shape.setPosition(x, y);
//	//	shape.setOutlineColor(sf::Color::White);
//	//	shape.setOutlineThickness(1.0f);
//	//	shape.setFillColor(sf::Color::Transparent);

//	//	window.draw(shape);
//	window.draw(text);
//}

static float get_final_x(const Node &node)
{
	return 800 + (node.x * 200);
}

static float get_final_y(const Node &node)
{
	return 800 + (node.y * 200);
}

static void add_neighbours(const std::vector<Room> &rooms, Node &node)
{

	for (auto &exit : node.room.get_exits()) {
		const auto &next_room =
		    std::find_if(rooms.begin(), rooms.end(), [&exit](const auto &r) { return r.get_id() == exit.room_id; });

		if (next_room == rooms.end())
			continue;

		const auto &existing_node = std::find_if(g_nodes.begin(), g_nodes.end(),
		                                         [&](const auto &n) { return n.room.get_id() == next_room->get_id(); });

		if (existing_node != g_nodes.end())
			continue;

		Node new_node{node.x, node.y, Room{*next_room}, {}};

		if (Hpta_strings::equals_ignorecase(exit.direction, "norden")) {
			--new_node.y;
		}
		else if (Hpta_strings::equals_ignorecase(exit.direction, "osten")) {
			++new_node.x;
		}
		else if (Hpta_strings::equals_ignorecase(exit.direction, "süden")) {
			++new_node.y;
		}
		else if (Hpta_strings::equals_ignorecase(exit.direction, "westen")) {
			--new_node.x;
		}

		g_nodes.emplace_back(new_node);

		// TODO: Link is only added to the node scoped in this function, not to that one in g_nodes
		node.links.emplace_back(Link{exit.direction, g_nodes.back()});

		add_neighbours(rooms, new_node);
	}
}

void Map::init()
{
	g_font.loadFromFile((Settings::gamedata_dir + "/fonts/Ubuntu-B.ttf"));

	Room_list::refresh_rooms();

	const auto rooms{Room_list::get_rooms()};

	if (rooms.empty())
		return;

	g_nodes.emplace_back(Node{0, 0, rooms.at(0), {}});

	add_neighbours(rooms, g_nodes.at(0));

	spdlog::debug("Sorting rooms: name\tx\ty\n");
	for (const auto &n : g_nodes) {
		spdlog::debug("{}\t{}\t{}\n", n.room.get_name(), n.x, n.y);
	}
}

void Map::refresh(sf::RenderWindow &window)
{
	for (auto &node : g_nodes) {
		auto text = sf::Text(node.room.get_name(), g_font);

		const float x = get_final_x(node);
		const float y = get_final_y(node);

		text.scale(0.5, 0.5);
		text.setPosition(x, y);
		window.draw(text);

		sf::RectangleShape shape({text.getGlobalBounds().width + 20, text.getGlobalBounds().height + 20});
		shape.setPosition(x - 10, y - 10);
		shape.setOutlineColor(sf::Color::White);
		shape.setOutlineThickness(1.0f);
		shape.setFillColor(sf::Color::Transparent);
		window.draw(shape);

		for (auto &link : node.links) {
			sf::RectangleShape marker({50, 50});

			marker.setPosition((x + get_final_x(link.target)) / 2, (y + get_final_y(link.target)) / 2);
			marker.setFillColor(sf::Color::Yellow);
			window.draw(marker);
		}
	}

	//	sf::RectangleShape shape({10, 10});
	//	shape.setPosition(10, 10);
	//	shape.setFillColor(sf::Color::Green);
	//	window.draw(shape);

	//	draw_room(window, "Zum tropfenden Kessel", 50, 50);
}
