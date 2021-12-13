#include "map.hpp"

#include <fmt/core.h>
#include <imgui-SFML.h>
#include <imgui.h>
#include <memory>
#include <spdlog/spdlog.h>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

#include "objects/room.hpp"
#include "room_list.hpp"
#include "settings.hpp"
#include "util/hpta_strings.hpp"

static auto g_font = sf::Font();

struct Link;

struct Node {
	Node(float _x, float _y, Room _room) : x(_x), y(_y), room(_room) {}

	float             x;
	float             y;
	Room              room;
	std::vector<Link> links = {};
};

struct Link {
	std::string           direction;
	std::shared_ptr<Node> target;
};

using Node_ptr = std::shared_ptr<Node>;

static std::vector<Node_ptr> g_nodes;

static void add_neighbours(const std::vector<Room> &rooms, Node_ptr &node)
{

	for (auto &exit : node->room.get_exits()) {
		const auto &next_room =
		    std::find_if(rooms.begin(), rooms.end(), [&exit](const auto &r) { return r.get_id() == exit.room_id; });

		if (next_room == rooms.end())
			continue;

		const auto &existing_node = std::find_if(
		    g_nodes.begin(), g_nodes.end(), [&](const auto &n) { return n->room.get_id() == next_room->get_id(); });

		// node already exists, nothing to do
		if (existing_node != g_nodes.end()) {
			node->links.emplace_back(Link{exit.direction, *existing_node});
			continue;
		}

		auto new_node = std::make_shared<Node>(node->x, node->y, Room{*next_room});

		if (Hpta_strings::equals_ignorecase(exit.direction, "norden")) {
			--new_node->y;
		}
		else if (Hpta_strings::equals_ignorecase(exit.direction, "osten")) {
			++new_node->x;
		}
		else if (Hpta_strings::equals_ignorecase(exit.direction, "süden")) {
			++new_node->y;
		}
		else if (Hpta_strings::equals_ignorecase(exit.direction, "westen")) {
			--new_node->x;
		}

		// TODO: Link is only added to the node scoped in this function, not to that one in g_nodes
		node->links.emplace_back(Link{exit.direction, new_node});

		g_nodes.emplace_back(new_node);
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

	Node_ptr nptr = std::make_shared<Node>(0, 0, rooms.at(0));

	g_nodes.emplace_back(nptr);

	add_neighbours(rooms, g_nodes.at(0));

	spdlog::debug("Sorting rooms: name\tx\ty\tlinks\n");
	for (const auto &n : g_nodes) {
		spdlog::debug("{}\t{}\t{}\t{}\n", n->room.get_name(), n->x, n->y, n->links.size());
	}
}

// static void draw_node(sf::RenderWindow &window, Node_ptr &node)
//{
//	constexpr float node_with   = 10;
//	constexpr float node_height = 10;

//	const float x = get_final_x(*node);
//	const float y = get_final_y(*node);

//	sf::RectangleShape node_rect{{node_with, node_height}};
//	node_rect.setPosition(x, y);
//	node_rect.setOutlineColor(sf::Color::White);
//	node_rect.setOutlineThickness(1.0f);
//	node_rect.setFillColor(sf::Color::White);
//	window.draw(node_rect);

//	auto text = sf::Text(node->room.get_name(), g_font);

//	text.scale(0.5, 0.5);
//	text.setPosition(x + 10, y + 10);
//	window.draw(text);

//	//	sf::RectangleShape shape({text.getGlobalBounds().width + 20, text.getGlobalBounds().height + 20});
//	//	shape.setPosition(x - 10, y - 10);
//	//	shape.setOutlineColor(sf::Color::White);
//	//	shape.setOutlineThickness(1.0f);
//	//	shape.setFillColor(sf::Color::Transparent);
//	//	window.draw(shape);
//}

constexpr float node_width        = 40;
constexpr float node_height       = 40;
constexpr float marker_width      = 20;
constexpr float marker_height     = 20;
constexpr float text_scale        = 0.7f;
constexpr float x_y_start         = 800;
constexpr float node_spread_scale = 300;

static float get_final_x(const Node &node)
{
	return x_y_start + (node.x * node_spread_scale);
}

static float get_final_y(const Node &node)
{
	return x_y_start + (node.y * node_spread_scale);
}

static float get_final_x_middle(const Node &n1, const Node &n2)
{

	return (get_final_x(n1) + get_final_x(n2) + node_width) / 2;
}

static float get_final_y_middle(const Node &n1, const Node &n2)
{
	return (get_final_y(n1) + get_final_y(n2) + node_height) / 2;
}

void Map::refresh(sf::RenderWindow &window)
{

	for (auto &node : g_nodes) {

		const float x = get_final_x(*node);
		const float y = get_final_y(*node);

		sf::RectangleShape node_rect{{node_width, node_height}};
		node_rect.setPosition(x, y);
		node_rect.setOutlineColor(sf::Color::White);
		node_rect.setOutlineThickness(1.0f);
		node_rect.setFillColor(sf::Color::Transparent);
		window.draw(node_rect);

		auto text = sf::Text(node->room.get_name(), g_font);

		text.scale(text_scale, text_scale);

		text.setPosition(x + node_width - text.getGlobalBounds().width / 2, y - node_height);
		window.draw(text);

		for (auto &link : node->links) {

			sf::CircleShape marker(marker_width / 2);
			//			sf::RectangleShape marker({marker_width, marker_height});

			marker.setPosition(get_final_x_middle(*node, *link.target) - marker_width / 2,
			                   get_final_y_middle(*node, *link.target) - marker_height / 2);
			marker.setFillColor(sf::Color::Yellow);
			window.draw(marker);
		}
	}
}
