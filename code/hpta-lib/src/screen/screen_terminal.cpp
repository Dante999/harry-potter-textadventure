#include "hpta-lib/screen/screen_terminal.hpp"

#include <cstdint>
#include <iostream>

#include <fmt/color.h>
#include <fmt/core.h>

void Screen_Terminal::hline()
{
    for (uint8_t i = 0; i < this->column_width; ++i) {
        fmt::print("-");
    }

    fmt::print("\n");
}

void Screen_Terminal::print(const std::string &msg)
{
    fmt::print(msg);
}

const std::string Screen_Terminal::ask_for(const std::string &msg)
{
    std::string input;

    this->print(msg);
    fmt::print(fg(fmt::color::steel_blue), ">>");
    getline(std::cin, input);
    fmt::print("\n");

    return input;
}

void Screen_Terminal::box_start(const std::string &caption)
{
    this->hline();
    this->print(caption + '\n');

    for (size_t i = 0; i < caption.length(); ++i) {
        this->print("=");
    }

    fmt::print("\n");
}

void Screen_Terminal::box_end()
{
    this->hline();
    this->print("\n");
}
