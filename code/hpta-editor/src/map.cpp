#include "hpta-editor/map.hpp"

#include <chrono>
#include <fmt/core.h>
#include <imgui-SFML.h>
#include <imgui.h>
#include <memory>
#include <spdlog/spdlog.h>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Mouse.hpp>

#include "hpta-editor/panel_room_attributes.hpp"
#include "hpta-editor/room_list.hpp"
#include "hpta-editor/settings.hpp"
#include "hpta-lib/objects/room.hpp"
#include "hpta-lib/util/hpta_algorithms.hpp"
#include "hpta-lib/util/hpta_strings.hpp"

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

	spdlog::debug("Sorting rooms: name\tx\ty\tlinks");
	for (const auto &n : g_nodes) {
		spdlog::debug("{}\t{}\t{}\t{}", n->room.get_name(), n->x, n->y, n->links.size());
	}
}

constexpr float node_width        = 40;
constexpr float node_height       = 40;
constexpr float marker_width      = 20;
constexpr float marker_height     = 20;
constexpr float text_scale        = 0.7f;
constexpr float x_start           = 300;
constexpr float y_start           = 800;
constexpr float node_spread_scale = 300;
constexpr float mouse_debounce_ms = 200;
constexpr float link_thickness    = 5;
constexpr float link_spacer       = 150;

static float get_final_x(const Node &node)
{
	return x_start + (node.x * node_spread_scale);
}

static float get_final_y(const Node &node)
{
	return y_start + (node.y * node_spread_scale);
}

static bool position_hits_node(int x, int y, const Node_ptr &node)
{
	return (Hpta_algorithms::is_between_or_equal(get_final_x(*node), get_final_x(*node) + node_width,
	                                             static_cast<float>(x)) &&
	        Hpta_algorithms::is_between_or_equal(get_final_y(*node), get_final_y(*node) + node_height,
	                                             static_cast<float>(y)));
}

static sf::Vector2f get_node_center(const Node &node)
{
	return {get_final_x(node) + (node_width / 2), get_final_y(node) + (node_height / 2)};
}

static void center_shape(float x, float y, sf::Shape &shape)
{
	shape.setPosition(x - (shape.getGlobalBounds().width / 2), y - (shape.getGlobalBounds().height / 2));
}

static std::tuple<sf::RectangleShape, sf::CircleShape> get_arrow(sf::Vector2f a, sf::Vector2f b, float space)
{
	float rect_x, rect_y, width, heigth;

	if (a.x == b.x) {
		rect_x = a.x;
		rect_y = Hpta_algorithms::get_middlepoint(a.y, b.y);
		width  = link_thickness;
		heigth = Hpta_algorithms::get_distance(a.y, b.y) - space;
	}
	else if (a.y == b.y) {
		rect_x = Hpta_algorithms::get_middlepoint(a.x, b.x);
		rect_y = a.y;
		width  = Hpta_algorithms::get_distance(a.x, b.x) - space;
		heigth = link_thickness;
	}
	else {
		rect_x = 0;
		rect_y = 0;
		width  = 1;
		heigth = 1;
	}

	auto line = sf::RectangleShape({width, heigth});
	center_shape(rect_x, rect_y, line);

	auto tip = sf::CircleShape(8, 4);
	center_shape(Hpta_algorithms::get_middlepoint(rect_x, b.x), Hpta_algorithms::get_middlepoint(rect_y, b.y), tip);

	return std::make_tuple(line, tip);
}

// static sf::CircleShape get_arrow(sf::RectangleShape line, sf::Vector2f target, float space)
//{
//	float x, y;

//	if (line.getGlobalBounds().height == link_thickness) {
//		// horizontal line
//		y = get_
//	}

//	float rect_x, rect_y;

//	if (source.x == target.x) {
//		rect_x = target.x;
//		rect_y = target.y - space;
//	}
//	else if (source.y == target.y) {
//		rect_x = target.x - space;
//		rect_y = target.y;
//	}
//	else {
//		rect_x = 0;
//		rect_y = 0;
//	}

//	auto rect = sf::CircleShape(10, 3);

//	center_shape(rect_x, rect_y, rect);

//	return rect;
//}

void Map::refresh(sf::RenderWindow &window)
{

	for (auto &node : g_nodes) {

		const float x = get_final_x(*node);
		const float y = get_final_y(*node);

		sf::RectangleShape node_rect{{node_width, node_height}};
		node_rect.setPosition(x, y);
		node_rect.setOutlineColor(sf::Color::White);
		node_rect.setOutlineThickness(1.0f);

		const auto position = sf::Mouse::getPosition(window);

		if (position_hits_node(position.x, position.y, node)) {
			node_rect.setFillColor(sf::Color::White);
		}
		else {
			node_rect.setFillColor(sf::Color::Transparent);
		}

		window.draw(node_rect);

		auto text = sf::Text(node->room.get_name(), g_font);

		text.scale(text_scale, text_scale);

		text.setPosition(x + node_width - text.getGlobalBounds().width / 2, y - node_height);
		window.draw(text);

		const auto node_center = get_node_center(*node);

		sf::RectangleShape center_marker({marker_width, marker_height});

		center_shape(node_center.x, node_center.y, center_marker);
		center_marker.setFillColor(sf::Color::Yellow);
		window.draw(center_marker);

		for (auto &link : node->links) {
			//			auto link_line  = get_line(get_node_center(*node), get_node_center(*link.target), link_spacer);
			auto link_arrow = get_arrow(get_node_center(*node), get_node_center(*link.target), link_spacer);

			window.draw(std::get<0>(link_arrow));
			window.draw(std::get<1>(link_arrow));
		}
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

		static auto last_time_pressed = std::chrono::system_clock::now();

		std::chrono::duration<float, std::milli> duration = std::chrono::system_clock::now() - last_time_pressed;

		if (duration.count() > mouse_debounce_ms) {
			const auto position = sf::Mouse::getPosition(window);

			for (const auto &node : g_nodes) {

				if (position_hits_node(position.x, position.y, node)) {
					spdlog::info("Clicked on node {}", node->room.get_name());
					Panel_room_attributes::set_room(node->room.get_id());
				}
			}

			last_time_pressed = std::chrono::system_clock::now();
		}
	}
}
