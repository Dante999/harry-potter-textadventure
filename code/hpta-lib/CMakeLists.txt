project(hpta-lib CXX)

add_library(${PROJECT_NAME} 
    src/screen/screen_terminal.cpp 
    src/interpreter.cpp
    src/commands/walk.cpp 
    src/commands/help.cpp 
    src/commands/inventory.cpp 
    src/commands/look.cpp 
    src/commands/take.cpp 
    src/commands/say.cpp
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
)

target_include_directories(${PROJECT_NAME} PUBLIC ./include)

target_link_libraries(${PROJECT_NAME} 
    PRIVATE project_options 
            project_warnings 
            CONAN_PKG::fmt 
            CONAN_PKG::rapidjson
)
