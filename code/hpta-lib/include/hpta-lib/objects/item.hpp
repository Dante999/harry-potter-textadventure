#ifndef ITEM_HPP
#define ITEM_HPP

#include "hpta-lib/objects/gameobject.hpp"
#include <string>

class Item : public Gameobject {
  private:
  public:
    explicit Item(const std::string &id) : Gameobject{id} {}
};

#endif // ITEM_HPP
