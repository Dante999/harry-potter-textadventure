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

    struct Secret {
        bool        is_revealed{false};
        std::string name;
        std::string description_before_reveal;
        std::string description_after_reveal;
        std::string text_on_reveal;
        std::string needs_spell_id;
        std::string needs_item_id;
        std::string needs_password;
        std::string reveals_item_id;
    };

  private:
    std::vector<Exit>   m_exits;
    std::vector<Detail> m_details;
    std::vector<Npc>    m_npcs;
    std::vector<Secret> m_secrets;

  public:
    explicit Room(const std::string &id) : Gameobject{id} {}

    void set_exits(const std::vector<Exit> &exits) { m_exits = exits; }
    void set_details(const std::vector<Detail> &details) { m_details = details; }
    void set_npcs(const std::vector<Npc> &npcs) { m_npcs = npcs; }
    void set_secrets(const std::vector<Secret> &secrets) { m_secrets = secrets; }

    [[nodiscard]] auto get_exits() const { return m_exits; }
    [[nodiscard]] auto get_details() const { return m_details; }
    [[nodiscard]] auto get_npcs() const { return m_npcs; }
    [[nodiscard]] auto get_secrets() const { return m_secrets; }
};

#endif /* ROOM_H */
