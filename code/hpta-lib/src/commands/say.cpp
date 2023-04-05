#include "hpta-lib/commands/say.hpp"

#include "hpta-lib/persistency/persistency.hpp"
#include "hpta-lib/services/cache_service.hpp"
#include "hpta-lib/services/user_interaction_service.hpp"
#include "hpta-lib/util/hpta_strings.hpp"

#include <fmt/core.h>

bool Say::interprete(Context &context, const std::vector<std::string> &token)
{
    const auto screen = context.service_registry.get<User_Interaction_Service>()->get_screen();

    if (!Hpta_strings::equals_one_of(token.at(0), {"sag", "sprich"}))
        return false;

    std::string text{};

    for (size_t i = 1; i < token.size(); ++i) {
        text += token.at(i);
    }

    auto &room = context.service_registry.get<Cache_Service>()->rooms->get_object(context.player->get_room_id());

    auto secrets = room.get_secrets();
    for (auto &secret : secrets) {
        
        if (secret.is_revealed || !secret.reveal_by_password ) {
            continue;
        }

        if (!Hpta_strings::equals_ignorecase(secret.reveal_by_password->password, text)) {
            continue;
        }
            
        secret.is_revealed = true;
                
        for (const auto reveal_action : secret.reveal_by_password->on_success_actions) {
            reveal_action(context);
        }
 
    }
    
    
    room.set_secrets(secrets);

    return true;
}
