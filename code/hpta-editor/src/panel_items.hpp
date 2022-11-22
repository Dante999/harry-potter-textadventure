#ifndef WINDOW_ITEMS_HPP
#define WINDOW_ITEMS_HPP

#include "panel_base.hpp"

#include "hpta-lib/objects/item.hpp"

class Panel_Items : public Panel_Base<Item> {

  private:
    Item_cache m_item_cache;

  public:
    Panel_Items(const std::string &name, Item_cache &cache) : Panel_Base{name}, m_item_cache{cache} {}

    void              create_object() override;
    void              load_object() override;
    std::vector<Item> get_objects() override;
    void              refresh_cache() override;
    void              save_object() override;
    void              show_attributes() override;
};

#endif /* WINDOW_ITEMS_HPP */
