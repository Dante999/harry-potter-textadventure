#ifndef ICOMMAND_H
#define ICOMMAND_H

#include <string>
#include <vector>

#include "hpta-lib/objects/player.hpp"
#include "hpta-lib/services/gameengine.hpp"

struct Context {
	Player &    player;
	Gameengine &gameengine;
};

class ICommand {
  public:
	virtual ~ICommand()                                                         = default;
	virtual const std::string get_command()                                     = 0;
	virtual const std::string get_description()                                 = 0;
	virtual bool              interprete(const std::vector<std::string> &token) = 0;
};

#endif /* ICOMMAND_H */
