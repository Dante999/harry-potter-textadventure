#ifndef ITEM_PERSISTENCY_HPP
#define ITEM_PERSISTENCY_HPP

#include "objects/item.hpp"

class Item_persistency {
  public:
	static Item load(const std::string &gamedata_dir, const std::string &filepath);
	static bool save(const std::string &gamedata_dir, const Item &item);
};

#endif // ITEM_PERSISTENCY_HPP
