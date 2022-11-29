#ifndef WINDOW_ITEMS_HPP
#define WINDOW_ITEMS_HPP

#include "panel_base.hpp"

#include "hpta-lib/objects/item.hpp"

class Panel_Items : public Panel_Base<Item> {

  public:
    Panel_Items(const std::string &name, World_Cache &world_cache) : Panel_Base{name, world_cache} {}

    void              create_object() override;
    void              load_object() override;
    std::vector<Item> get_objects() override;
    void              refresh_cache() override;
    void              save_object() override;
    void              show_attributes() override;
};

#endif /* WINDOW_ITEMS_HPP */
