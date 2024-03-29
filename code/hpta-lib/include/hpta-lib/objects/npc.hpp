#ifndef NPC_HPP
#define NPC_HPP

#include <string>
#include <vector>

#include "hpta-lib/objects/gameobject.hpp"
#include "hpta-lib/objects/storage.hpp"

class Npc : public Storage, public Gameobject {

  private:
    std::vector<std::string> m_phrases;

  public:
    explicit Npc(const std::string &id) : Gameobject{id} {}

    void set_phrases(const std::vector<std::string> &phrases) { m_phrases = phrases; }

    [[nodiscard]] auto get_phrases() const { return m_phrases; }
};

#endif /* NPC_HPP */
