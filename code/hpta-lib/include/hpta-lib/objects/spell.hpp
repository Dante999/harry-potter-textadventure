#ifndef SPELL_HPP
#define SPELL_HPP

#include "hpta-lib/objects/gameobject.hpp"
#include <string>

class Spell : public Gameobject {
  public:
    explicit Spell(const std::string &id) : Gameobject{id} {}
};

#endif /* SPELL_HPP */
