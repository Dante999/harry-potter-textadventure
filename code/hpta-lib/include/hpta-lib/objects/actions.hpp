#ifndef ACTIONS_HPP
#define ACTIONS_HPP

#include "hpta-lib/context.hpp"

#include <functional>
#include <optional>
#include <any>

using Action = std::function<void(Context &context)>;

std::optional<Action> create_action(const std::string& action_id, std::any value);

#endif /* ACTIONS_HPP */
