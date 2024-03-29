#include "hpta-lib/screen/screen_terminal.hpp"

#include "hpta-lib/util/hpta_strings.hpp"

#include <algorithm>
#include <cstdint>
#include <iostream>

#include <fmt/color.h>
#include <fmt/core.h>

const std::string Screen_Terminal::highlight(const std::string &msg)
{
    std::string result{msg};
    std::transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

void Screen_Terminal::hline()
{
    for (uint8_t i = 0; i < this->column_width; ++i) {
        fmt::print("-");
    }

    fmt::print("\n");
}

void Screen_Terminal::print(const std::string &msg) { fmt::print(msg); }
void Screen_Terminal::println(const std::string &msg) { fmt::print("{}\n", msg); }

void Screen_Terminal::print_wrapped(const std::string &msg)
{
    const auto lines = Hpta_strings::split_text_into_lines(msg, column_width);

    for (const auto &line : lines) {
        println(line);
    }
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
