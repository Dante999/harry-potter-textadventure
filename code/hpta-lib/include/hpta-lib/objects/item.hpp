#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>
#include "hpta-lib/objects/gameobject.hpp"

class Item : public Gameobject {
  private:


  public:
	// clang-format off
	explicit Item(const std::string& id) : Gameobject{id} {}
	// clang-format on
};

#endif // ITEM_HPP
