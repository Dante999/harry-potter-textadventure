#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <vector>

#include "hpta-lib/objects/gameobject.hpp"
#include "hpta-lib/objects/npc.hpp"
#include "hpta-lib/objects/storage.hpp"
#include "hpta-lib/objects/actions.hpp"

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

    struct Reveal_By_Spell {
        std::string spell_id;
        int difficulty;
        std::vector<Action> on_success_actions{};
        std::vector<Action> on_crit_success_actions{};
        std::vector<Action> on_failure_actions{};
        std::vector<Action> on_crit_failure_actions{};
    };
    
    struct Reveal_By_Item {
        std::string item_id;
        bool item_gets_destroyed;
        std::vector<Action> on_success_actions{};
    };
    
        struct Reveal_By_Password {
        std::string item_id;
        bool item_gets_destroyed;
        std::vector<Action> on_success_actions{};
    };
    
    struct Secret {
        bool        is_revealed{false};
        std::string name;
        std::string description_before_reveal;
        std::string description_after_reveal;
        std::string description_on_reveal;
        std::optional<Reveal_By_Spell> reveal_by_spell;
        std::optional<Reveal_By_Item> reveal_by_item;
        std::optional<Reveal_By_Password> reveal_by_password;
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
