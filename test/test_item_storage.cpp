#include <gtest/gtest.h>

#include "hpta-lib/objects/storage.hpp"

TEST(ItemStorage, emptyStorage)
{
	Storage sut;

	ASSERT_EQ(0, sut.get_items().size());
}

TEST(ItemStorage, addItem)
{
	Storage sut;

	sut.add_item({10, Item("my-id")});

	ASSERT_EQ(1, sut.get_items().size());
	ASSERT_EQ(10, sut.get_items().at(0).quantity);
	ASSERT_EQ("my-id", sut.get_items().at(0).item.get_id());
}

TEST(ItemStorage, addItemToExisting)
{
	Storage sut;

	sut.add_item({10, Item("my-id")});
	sut.add_item({10, Item("my-id")});

	ASSERT_EQ(1, sut.get_items().size());
	ASSERT_EQ(20, sut.get_items().at(0).quantity);
	ASSERT_EQ("my-id", sut.get_items().at(0).item.get_id());
}

TEST(ItemStorage, removeItem)
{
	Storage sut;

	sut.add_item({10, Item("my-id")});
	sut.remove_item({7, Item("my-id")});

	ASSERT_EQ(1, sut.get_items().size());
	ASSERT_EQ(3, sut.get_items().at(0).quantity);
	ASSERT_EQ("my-id", sut.get_items().at(0).item.get_id());
}
