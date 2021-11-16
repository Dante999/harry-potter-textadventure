#include "services/registry.hpp"

Persistence Registry::m_persistence  = Persistence();
Gameengine  Registry::m_gameengine   = Gameengine();
std::string Registry::m_gamedata_dir = "gamedata";

Gameengine &Registry::get_gameengine()
{
	return m_gameengine;
}
Persistence &Registry::get_persistence()
{
	return m_persistence;
}
