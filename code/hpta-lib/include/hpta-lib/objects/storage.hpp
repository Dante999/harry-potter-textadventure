#ifndef STORAGE_H
#define STORAGE_H

#include "hpta-lib/objects/item.hpp"

#include <vector>

class Storage {

  public:
    struct Entry {
        int  quantity;
        Item item;
    };

  private:
    std::vector<Entry> m_items;

  private:
    [[nodiscard]] auto find_entry(const Item &item);

  public:
    int  add_item(const Entry &entry);
    int  remove_item(const Entry &&entry);
    void delete_items();

    [[nodiscard]] auto &get_items() const { return m_items; }
};

#endif /* STORAGE_H */
