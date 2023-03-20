#ifndef CACHE_SERVICE_HPP
#define CACHE_SERVICE_HPP

#include <map>
#include <memory>
#include <string>

#include "hpta-lib/objects/spell.hpp"
#include "hpta-lib/persistency/persistency.hpp"

template <typename TGame_Object, auto TloadFunction>
class Object_Cache;

using Room_Cache  = Object_Cache<Room, persistency::load_room>;
using Spell_Cache = Object_Cache<Spell, persistency::load_spell>;

class Cache_Service {
  private:
    const std::string m_gamedata_dir;

  public:
    std::unique_ptr<Spell_Cache> spells;
    std::unique_ptr<Room_Cache>  rooms;

  public:
    explicit Cache_Service(const std::string &gamedata_dir)
        : m_gamedata_dir{gamedata_dir}, spells{std::make_unique<Spell_Cache>(gamedata_dir)},
          rooms{std::make_unique<Room_Cache>(gamedata_dir)}
    {
    }
};

template <typename TGame_Object, auto TloadFunction>
class Object_Cache {

  private:
    std::map<std::string, TGame_Object> m_objects;
    const std::string                   m_gamedata_dir;

  public:
    explicit Object_Cache(const std::string &gamedata_dir) : m_gamedata_dir{gamedata_dir} {}

    TGame_Object &get_object(const std::string &id)
    {
        if (m_objects.find(id) == m_objects.end()) {
            auto object = TloadFunction(m_gamedata_dir, id);
            m_objects.insert({object.get_id(), object});
        }

        return m_objects.find(id)->second;
    }
};

#endif // ROOM_CACHE_SERVICE_HPP
