#include <gtest/gtest.h>

#include "hpta-lib/objects/item_storage.hpp"

TEST(ItemStorage, emptyStorage)
{
	Item_storage sut;

	ASSERT_EQ(0, sut.get_items().size());
}

TEST(ItemStorage, addItem)
{
	Item_storage sut;

	sut.add_item({10, Item("my-id")});

	ASSERT_EQ(1, sut.get_items().size());
	ASSERT_EQ(10, sut.get_items().at(0).quantity);
	ASSERT_EQ("my-id", sut.get_items().at(0).item.get_id());
}

TEST(ItemStorage, addItemToExisting)
{
	Item_storage sut;

	sut.add_item({10, Item("my-id")});
	sut.add_item({10, Item("my-id")});

	ASSERT_EQ(1, sut.get_items().size());
	ASSERT_EQ(20, sut.get_items().at(0).quantity);
	ASSERT_EQ("my-id", sut.get_items().at(0).item.get_id());
}

TEST(ItemStorage, removeItem)
{
	Item_storage sut;

	sut.add_item({10, Item("my-id")});
	sut.remove_item({7, Item("my-id")});

	ASSERT_EQ(1, sut.get_items().size());
	ASSERT_EQ(3, sut.get_items().at(0).quantity);
	ASSERT_EQ("my-id", sut.get_items().at(0).item.get_id());
}
