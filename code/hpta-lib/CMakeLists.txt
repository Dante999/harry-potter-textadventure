project(hpta-lib CXX)

add_library(${PROJECT_NAME}
    src/screen.cpp
    src/interpreter.cpp
    src/commands/walk.cpp
    src/commands/help.cpp
    src/commands/inventory.cpp
    src/commands/look.cpp
    src/commands/take.cpp
    src/objects/storage.cpp
    src/visualizer.cpp
    src/persistency/room_persistency.cpp
    src/persistency/item_persistency.cpp
    src/persistency/npc_persistency.cpp
    src/persistency/json_filehandler.hpp	
    src/util/hpta_string.cpp
    src/util/hpta_config.cpp
    src/services/room_cache_service.cpp
    src/services/player_walk_service.cpp
    include/hpta-lib/persistency/persistency.hpp
	include/hpta-lib/services/room_cache_service.hpp
	include/hpta-lib/services/player_walk_service.hpp
	include/hpta-lib/services/service_registry.hpp
	include/hpta-lib/persistency/persistency.hpp
	include/hpta-lib/visualizer.hpp
	include/hpta-lib/screen.hpp
	include/hpta-lib/objects/gameobject.hpp
	include/hpta-lib/objects/item.hpp
	include/hpta-lib/objects/player.hpp
	include/hpta-lib/objects/storage.hpp
	include/hpta-lib/objects/npc.hpp
	include/hpta-lib/objects/room.hpp
	include/hpta-lib/commands/look.hpp
	include/hpta-lib/commands/icommand.hpp
	include/hpta-lib/commands/inventory.hpp
	include/hpta-lib/commands/take.hpp
	include/hpta-lib/commands/walk.hpp
	include/hpta-lib/commands/help.hpp
	include/hpta-lib/interpreter.hpp
	include/hpta-lib/util/hpta_strings.hpp
	include/hpta-lib/util/hpta_config.hpp
	include/hpta-lib/util/hpta_algorithms.hpp
)

target_include_directories(${PROJECT_NAME} PUBLIC ./include)

target_link_libraries(${PROJECT_NAME} 
    PRIVATE project_options 
            project_warnings
            CONAN_PKG::fmt
            CONAN_PKG::rapidjson
)
