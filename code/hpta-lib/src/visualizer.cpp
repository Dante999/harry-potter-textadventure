#include "hpta-lib/visualizer.hpp"

#include <fmt/core.h>

#include "hpta-lib/util/hpta_algorithms.hpp"
#include "hpta-lib/util/hpta_strings.hpp"

void Visualizer::show(const Room &room)
{

    m_screen->box_start(room.get_name());

    for (const auto &line : Hpta_strings::split_text_into_lines(room.get_description(), m_screen->column_width)) {
        m_screen->print(line + "\n");
    }

    m_screen->print("\n");
    for (auto &npc : room.get_npcs()) {
        std::string phrase = hpta::get_random_entry(npc.get_phrases());
        m_screen->print(fmt::format("{} sagt: {}\n", npc.get_name(), phrase));
    }

    m_screen->print("\n");

    if (!room.get_items().empty()) {
        m_screen->print("In deiner Umgebung befindet sich: \n");
        for (auto &item : room.get_items()) {
            m_screen->print(fmt::format("\t{}x {}\n", item.quantity, item.item.get_name()));
        }
    }

    m_screen->print("\n");
    m_screen->print("Mögliche Richtungen:\n");
    for (const auto &exit : room.get_exits()) {
        m_screen->print(fmt::format("\t{}\t-> {}\n", exit.direction, exit.description));
    }

    m_screen->box_end();
}

void Visualizer::show(const Player &player)
{
    m_screen->box_start(player.get_name());

    m_screen->print("Inventar:\n");
    for (auto &item : player.get_items()) {
        m_screen->print(fmt::format("\t{}x {}\n", item.quantity, item.item.get_name()));
    }

    //	m_screen->print(fmt::format("Stärke ............ {}\n", player.get_strength()));
    //	m_screen->print(fmt::format("Geschicklichkeit .. {}\n", player.get_dextery()));
    //	m_screen->print(fmt::format("Vitalität ......... {}\n", player.get_vitality()));
    //	m_screen->print(fmt::format("Magie ............. {}\n", player.get_magic()));
    m_screen->box_end();
}

void Visualizer::show(const Item &item)
{
    m_screen->box_start(item.get_name());

    for (const auto &line : Hpta_strings::split_text_into_lines(item.get_description(), m_screen->column_width)) {
        m_screen->print(line + "\n");
    }

    m_screen->box_end();
}

void Visualizer::show(const Room::Detail &detail)
{
    m_screen->box_start(detail.name);

    for (const auto &line : Hpta_strings::split_text_into_lines(detail.description, m_screen->column_width)) {
        m_screen->print(line + "\n");
    }

    m_screen->box_end();
}
