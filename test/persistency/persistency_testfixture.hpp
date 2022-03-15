#ifndef PERSISTENCY_TESTFIXTURE_HPP
#define PERSISTENCY_TESTFIXTURE_HPP

#include <gtest/gtest.h>

#include <filesystem>
#include <string>
#include <vector>

enum class Category { ITEMS, ROOMS, NPCS };

class Persistency_test_fixture : public ::testing::Test {
  protected:
	// TODO: Replace me with a configurable or auto detected value
	std::string m_gamedata_dir{
	    "/home/dante999/Projekte/pc-textadventure/2_Software/harry-potter-textadventure/gamedata"};

	std::string m_tmp_gamedata_dir;

  private:
	void prepare_tmp_gamedata_dir(const std::string &test_name)
	{
		m_tmp_gamedata_dir = ::testing::TempDir() + "hpta-unittests/" + test_name;


		std::filesystem::create_directories(m_tmp_gamedata_dir);
		std::filesystem::copy(m_gamedata_dir, m_tmp_gamedata_dir, std::filesystem::copy_options::recursive);
	}

  public:
	Persistency_test_fixture()  = default;
	~Persistency_test_fixture() = default;

	const auto& get_tmp_gamedata_dir() {return m_tmp_gamedata_dir;}


	void TearDown() override
	{
		std::filesystem::remove_all(m_tmp_gamedata_dir);
	}

	std::vector<std::string> prepare_and_get_ids(const std::string &test_name, Category category)
	{
		prepare_tmp_gamedata_dir(test_name);
		

		std::vector<std::string> result;

		const auto base_dir = [&category]() {
			switch (category) {
			case Category::ITEMS:
				return "/items";
			case Category::NPCS:
				return "/npcs";
			case Category::ROOMS:
				return "/rooms";
			default:
				return "";
			}
		};

		for (const auto &file : std::filesystem::recursive_directory_iterator(m_gamedata_dir + base_dir())) {

			if (!file.is_directory()) {
				std::string id{file.path()};

				result.emplace_back(id.erase(0, m_gamedata_dir.length()));
			}
		}

		for (const auto &id : result) {
			std::filesystem::remove(m_tmp_gamedata_dir + id);
		}

		return result;
	}
};

#endif /* PERSISTENCY_TESTFIXTURE_HPP */
