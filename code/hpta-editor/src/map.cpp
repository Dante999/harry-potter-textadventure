#include "map.hpp"

#include <imgui-SFML.h>
#include <imgui.h>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

#include "settings.hpp"

static auto g_font = sf::Font();

static void draw_room(sf::RenderWindow &window, const std::string &id, float x, float y)
{
	auto text = sf::Text(id, g_font);
	text.setPosition(x, y);
	//	text.setScale(1.5, 1.5);

	//	sf::RectangleShape shape({text.getGlobalBounds().width + 10, text.getGlobalBounds().height + 10});
	//	shape.setPosition(x, y);
	//	shape.setOutlineColor(sf::Color::White);
	//	shape.setOutlineThickness(1.0f);
	//	shape.setFillColor(sf::Color::Transparent);

	//	window.draw(shape);
	window.draw(text);
}

void Map::init()
{
	g_font.loadFromFile((Settings::gamedata_dir + "/fonts/Ubuntu-B.ttf"));
}

void Map::refresh(sf::RenderWindow &window)
{
	sf::RectangleShape shape({10, 10});
	shape.setPosition(10, 10);
	shape.setFillColor(sf::Color::Green);
	window.draw(shape);

	draw_room(window, "Zum tropfenden Kessel", 50, 50);
}
