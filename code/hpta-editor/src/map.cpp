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

float g_room_object_width;
float g_room_object_height;
float g_room_link_thickness;
float g_room_link_margin;
float g_room_link_arrow_size;
float g_room_spread_factor;
float g_room_center_width;
float g_room_center_height;
float g_font_scale;
float g_map_start_x;
float g_map_start_y;
float g_mouse_debounce_ms;

static void init_config_values()
{
	g_font_scale           = Hpta_config::get_float(Settings::editor_font_scale);
	g_room_object_width    = Hpta_config::get_float(Settings::room_object_width);
	g_room_object_height   = Hpta_config::get_float(Settings::room_object_height);
	g_room_link_thickness  = Hpta_config::get_float(Settings::room_link_thickness);
	g_room_link_margin     = Hpta_config::get_float(Settings::room_link_margin);
	g_room_spread_factor   = Hpta_config::get_float(Settings::room_spread_factor);
	g_room_center_width    = Hpta_config::get_float(Settings::room_center_width);
	g_room_center_height   = Hpta_config::get_float(Settings::room_center_height);
	g_map_start_x          = Hpta_config::get_float(Settings::map_start_x);
	g_map_start_y          = Hpta_config::get_float(Settings::map_start_y);
	g_mouse_debounce_ms    = Hpta_config::get_float(Settings::mouse_debounce_ms);
	g_room_link_arrow_size = Hpta_config::get_float(Settings::room_link_arrow_size);
}

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

static float get_final_x(const Node &node)
{
	return g_map_start_x + (node.x * g_room_spread_factor);
}

static float get_final_y(const Node &node)
{
	return g_map_start_y + (node.y * g_room_spread_factor);
}

static bool position_hits_node(int x, int y, const Node_ptr &node)
{
	return (Hpta_algorithms::is_between_or_equal(get_final_x(*node), get_final_x(*node) + g_room_object_width,
	                                             static_cast<float>(x)) &&
	        Hpta_algorithms::is_between_or_equal(get_final_y(*node), get_final_y(*node) + g_room_object_height,
	                                             static_cast<float>(y)));
}

static sf::Vector2f get_node_center(const Node &node)
{
	return {get_final_x(node) + (g_room_object_width / 2), get_final_y(node) + (g_room_object_height / 2)};
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
		width  = g_room_link_thickness;
		heigth = Hpta_algorithms::get_distance(a.y, b.y) - space;
	}
	else if (a.y == b.y) {
		rect_x = Hpta_algorithms::get_middlepoint(a.x, b.x);
		rect_y = a.y;
		width  = Hpta_algorithms::get_distance(a.x, b.x) - space;
		heigth = g_room_link_thickness;
	}
	else {
		rect_x = 0;
		rect_y = 0;
		width  = 1;
		heigth = 1;
	}

	auto line = sf::RectangleShape({width, heigth});
	center_shape(rect_x, rect_y, line);

	auto tip = sf::CircleShape(g_room_link_arrow_size, 4);
	center_shape(Hpta_algorithms::get_middlepoint(rect_x, b.x), Hpta_algorithms::get_middlepoint(rect_y, b.y), tip);

	return std::make_tuple(line, tip);
}

void Map::init()
{
	g_nodes.clear();
	g_font.loadFromFile(Hpta_config::get_string(Settings::gamedata_dir) + "/fonts/" +
	                    Hpta_config::get_string(Settings::editor_font));

	init_config_values();

	Room_list::refresh_rooms();

	const auto rooms{Room_list::get_rooms()};

	if (rooms.empty())
		return;

	Node_ptr nptr = std::make_shared<Node>(0, 0, rooms.at(0));

	g_nodes.emplace_back(nptr);

	add_neighbours(rooms, g_nodes.at(0));

	for (const auto &n : g_nodes) {
		spdlog::debug("logical room position {}\tx={}\ty={}\tlinks={}", n->room.get_name(), n->x, n->y,
		              n->links.size());
	}
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

		sf::RectangleShape node_rect{{g_room_object_width, g_room_object_height}};
		node_rect.setPosition(x, y);
		node_rect.setOutlineColor(sf::Color::White);
		node_rect.setOutlineThickness(1.0f);

		const auto pixelPos = sf::Mouse::getPosition(window);
		const auto position = window.mapPixelToCoords(pixelPos);

		if (position_hits_node(static_cast<int>(position.x), static_cast<int>(position.y), node)) {
			node_rect.setFillColor(sf::Color::White);
		}
		else {
			node_rect.setFillColor(sf::Color::Transparent);
		}

		window.draw(node_rect);

		std::string room_name{node->room.get_name()};
		auto        text = sf::Text(sf::String::fromUtf8(room_name.begin(), room_name.end()), g_font);

		text.scale(g_font_scale, g_font_scale);

		text.setPosition(x + g_room_object_width - text.getGlobalBounds().width / 2, y - g_room_object_height);
		window.draw(text);

		const auto node_center = get_node_center(*node);

		sf::RectangleShape center_marker({g_room_center_width, g_room_center_height});

		center_shape(node_center.x, node_center.y, center_marker);
		center_marker.setFillColor(sf::Color::Yellow);
		window.draw(center_marker);

		for (auto &link : node->links) {
			//			auto link_line  = get_line(get_node_center(*node), get_node_center(*link.target), link_spacer);
			auto link_arrow = get_arrow(get_node_center(*node), get_node_center(*link.target), g_room_link_margin);

			window.draw(std::get<0>(link_arrow));
			window.draw(std::get<1>(link_arrow));
		}
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

		static auto last_time_pressed = std::chrono::system_clock::now();

		std::chrono::duration<float, std::milli> duration = std::chrono::system_clock::now() - last_time_pressed;

		if (duration.count() > g_mouse_debounce_ms) {
			const auto pixelPos = sf::Mouse::getPosition(window);
			const auto position = window.mapPixelToCoords(pixelPos);

			for (const auto &node : g_nodes) {

				if (position_hits_node(static_cast<int>(position.x), static_cast<int>(position.y), node)) {
					spdlog::info("Clicked on node {}", node->room.get_name());
					Panel_room_attributes::set_room(node->room.get_id());
				}
			}

			last_time_pressed = std::chrono::system_clock::now();
		}
	}
}
