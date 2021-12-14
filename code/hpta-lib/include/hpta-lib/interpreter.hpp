#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <memory>
#include <string>
#include <vector>

#include "hpta-lib/commands/icommand.hpp"

class Interpreter {

  private:
	std::vector<std::shared_ptr<ICommand>> m_commands;

  private:
	static const std::vector<std::string> split_text_by_words(const std::string &text);

  public:
	Interpreter();
	void parse(const std::string &text);
};

#endif /* INTERPRETER_H */
