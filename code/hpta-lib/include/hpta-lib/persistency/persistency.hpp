#ifndef PERSISTENCY_HPP
#define PERSISTENCY_HPP

#include "hpta-lib/objects/item.hpp"
#include "hpta-lib/objects/npc.hpp"
#include "hpta-lib/objects/room.hpp"
#include "hpta-lib/objects/spell.hpp"

namespace persistency {
[[nodiscard]] Room load_room(const std::string &gamedata_dir, const std::string &id);
[[nodiscard]] Item load_item(const std::string &gamedata_dir, const std::string &id);
[[nodiscard]] Npc  load_npc(const std::string &gamedata_dir, const std::string &id);
[[nodiscard]] Spell load_spell(const std::string &gamedata_dir, const std::string &id);

bool save_room(const std::string &gamedata_dir, const Room &room);
bool save_item(const std::string &gamedata_dir, const Item &item);
bool save_npc(const std::string &gamedata_dir, const Npc &npc);
bool save_spell(const std::string &gamedata_dir, const Spell &spell);
} // namespace persistency

#endif /* PERSISTENCY_HPP */
