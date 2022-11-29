#ifndef OBJECT_CACHE_HPP
#define OBJECT_CACHE_HPP

#include <algorithm>
#include <filesystem>
#include <vector>
#include <memory>

#include <spdlog/spdlog.h>

#include "hpta-lib/persistency/persistency.hpp"
#include "hpta-lib/util/hpta_config.hpp"
#include "settings.hpp"

template <typename Tobject, auto TloadFunction>
class Object_cache;

using Item_cache  = Object_cache<Item, persistency::load_item>;
using Room_cache  = Object_cache<Room, persistency::load_room>;
using Spell_Cache = Object_cache<Spell, persistency::load_spell>;

struct World_Cache {
    std::unique_ptr<Item_cache> items;
    std::unique_ptr<Room_cache> rooms;
    std::unique_ptr<Spell_Cache> spells;

    World_Cache(const std::string& gamedata_dir) 
    : items{std::make_unique<Item_cache>(gamedata_dir, "/items")},
      rooms{std::make_unique<Room_cache>(gamedata_dir, "/rooms")},
      spells{std::make_unique<Spell_Cache>(gamedata_dir, "/spells")}
      {}
};





template <typename Tobject, auto TloadFunction>
class Object_cache {
  private:
    std::vector<Tobject> m_objects;
    std::string          m_gamedata_dir;
    std::string          m_objects_dir;

  public:
    Object_cache(const std::string &gamedata_dir, const std::string &objects_dir)
        : m_gamedata_dir{gamedata_dir}, m_objects_dir{objects_dir}
    {
        refresh();
    }

    void refresh()
    {
        m_objects.clear();

        for (const auto &file : std::filesystem::recursive_directory_iterator(m_gamedata_dir + m_objects_dir)) {

            if (file.is_directory())
                continue;

            const auto item_id = file.path().string().substr(m_gamedata_dir.length());

            if (Hpta_strings::ends_with(item_id, ".json")) {
                spdlog::info("loading object {}", item_id);
            }
            else {
                spdlog::warn("skipping unknown file {}", item_id);
                continue;
            }

            m_objects.emplace_back(TloadFunction(m_gamedata_dir, item_id));
        }

        std::sort(m_objects.begin(), m_objects.end(), [](auto a, auto b) { return a.get_id() < b.get_id(); });
    }

    std::vector<Tobject> get_list() { return m_objects; }
};

#endif // OBJECT_CACHE_HPP
