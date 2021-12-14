#ifndef REGISTRY_H
#define REGISTRY_H

#include "hpta-lib/services/gameengine.hpp"
#include "hpta-lib/services/persistence.hpp"

class Registry {
  private:
	static Persistence m_persistence;
	static Gameengine  m_gameengine;

  public:
	static std::string m_gamedata_dir;

  public:
	static Gameengine & get_gameengine();
	static Persistence &get_persistence();
};

#endif /* REGISTRY_H */
