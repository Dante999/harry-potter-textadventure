#ifndef SPELL_HPP
#define SPELL_HPP

#include "hpta-lib/objects/gameobject.hpp"
#include <string>

class Spell : public Gameobject {
  public:
    static constexpr double max_level{100};

  private:
    double m_level{1};

  public:
    explicit Spell(const std::string &id) : Gameobject{id} {}

    [[nodiscard]] auto get_level() const { return m_level; }

    void set_level(double level) { m_level = (level < max_level ? level : max_level); }
};

#endif /* SPELL_HPP */
