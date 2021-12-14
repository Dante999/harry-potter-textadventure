#include "hpta-lib/screen.hpp"

#include <cstdint>
#include <iostream>

#include <fmt/color.h>
#include <fmt/core.h>

namespace Screen {

void hline()
{
	for (uint8_t i = 0; i < Screen::column_width; ++i) {
		fmt::print("-");
	}

	fmt::print("\n");
}

void print(const std::string &msg)
{
	fmt::print(msg);
}

const std::string ask_for(const std::string &msg)
{
	std::string input;

	Screen::print(msg);
	fmt::print(fg(fmt::color::steel_blue), ">>");
	getline(std::cin, input);
	fmt::print("\n");

	return input;
}

void box_start(const std::string &caption)
{
	Screen::hline();
	Screen::print(caption + '\n');

	for (size_t i = 0; i < caption.length(); ++i) {
		Screen::print("=");
	}

	fmt::print("\n");
}

void box_end()
{
	Screen::hline();
	Screen::print("\n");
}

} // namespace Screen
