#include "persistency_testfixture.hpp"

#include "hpta-lib/persistency/persistency.hpp"

#include <filesystem>
/*
 * TODO:
 * iterate over all existing items and:
 * - load them from the filesystem (see if this fails)
 * - save them into a temp directory
 * - load them again from the temp directory and compare them with the origin ones
 */
static void compare(const Item &lhs, const Item &rhs)
{
	EXPECT_EQ(lhs.get_id(), rhs.get_id());
	EXPECT_EQ(lhs.get_name(), rhs.get_name());
	EXPECT_EQ(lhs.get_description(), rhs.get_description());
}

static void compare(const Npc &lhs, const Npc &rhs)
{
	EXPECT_EQ(lhs.get_id(), rhs.get_id());
	EXPECT_EQ(lhs.get_name(), rhs.get_name());
	EXPECT_EQ(lhs.get_description(), rhs.get_description());
	EXPECT_EQ(lhs.get_phrases(), rhs.get_phrases());
}

static void compare(const Room &lhs, const Room &rhs)
{
	EXPECT_EQ(lhs.get_id(), rhs.get_id());
	EXPECT_EQ(lhs.get_name(), rhs.get_name());
	EXPECT_EQ(lhs.get_description(), rhs.get_description());
}

TEST_F(Persistency_test_fixture, item_persistency)
{
	const auto ids = prepare_and_get_ids("item_persistency", Category::ITEMS);

	for (const auto &id : ids) {
		const auto item = persistency::load_item(m_gamedata_dir, id);

		persistency::save_item(m_tmp_gamedata_dir, item);
		const auto item2 = persistency::load_item(m_tmp_gamedata_dir, id);

		compare(item, item2);
	}

}

TEST_F(Persistency_test_fixture, npc_persistency)
{
	const auto ids = prepare_and_get_ids("npc_persistency", Category::NPCS);

	for (const auto &id : ids) {
		const auto npc = persistency::load_npc(m_gamedata_dir, id);		

		persistency::save_npc(m_tmp_gamedata_dir, npc);
		const auto npc2 = persistency::load_npc(m_tmp_gamedata_dir, id);

		compare(npc, npc2);
	}

}

TEST_F(Persistency_test_fixture, room_persistency)
{
	const auto ids = prepare_and_get_ids("room_persistency", Category::ROOMS);

	for (const auto &id : ids) {
		const auto room = persistency::load_room(m_gamedata_dir, id);		

		persistency::save_room(m_tmp_gamedata_dir, room);
		const auto room2 = persistency::load_room(m_tmp_gamedata_dir, id);

		compare(room, room2);
	}

}