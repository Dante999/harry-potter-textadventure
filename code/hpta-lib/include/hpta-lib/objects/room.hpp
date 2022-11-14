#ifndef ROOM_H
#define ROOM_H

#include <map>
#include <string>
#include <vector>

#include "hpta-lib/objects/gameobject.hpp"
#include "hpta-lib/objects/npc.hpp"
#include "hpta-lib/objects/storage.hpp"

class Room : public Storage, public Gameobject {
  public:
    struct Exit {
        std::string direction;
        std::string description;
        std::string room_id;
    };

    struct Detail {
        std::string name;
        std::string description;
    };

  private:
    std::vector<Exit>   m_exits;
    std::vector<Detail> m_details;
    std::vector<Npc>    m_npcs;

  public:
    explicit Room(const std::string &id) : Gameobject{id} {}

    void set_exits(const std::vector<Exit> &exits) { m_exits = exits; }
    void set_details(const std::vector<Detail> &details) { m_details = details; }
    void set_npcs(const std::vector<Npc> &npcs) { m_npcs = npcs; }

    [[nodiscard]] auto get_exits() const { return m_exits; }
    [[nodiscard]] auto get_details() const { return m_details; }
    [[nodiscard]] auto get_npcs() const { return m_npcs; }
};

#endif /* ROOM_H */
