project(hpta-lib CXX)

add_library(${PROJECT_NAME}
    src/screen.cpp
    src/interpreter.cpp
    src/commands/walk.cpp
    src/commands/help.cpp
    src/commands/inventory.cpp
    src/commands/look.cpp
    src/commands/take.cpp
    src/objects/item_storage.cpp
    src/services/persistence.cpp
    src/services/gameengine.cpp
    src/services/registry.cpp
    src/visualizer.cpp
    src/persistency/room_persistency.cpp
    src/persistency/item_persistency.cpp
    src/util/hpta_string.cpp
    include/util/hpta_strings.hpp
    include/services/persistence.hpp
    include/services/registry.hpp
    include/services/gameengine.hpp
    include/persistency/room_persistency.hpp
    include/persistency/item_persistency.hpp
    include/visualizer.hpp
    include/screen.hpp
    include/objects/player.hpp
    include/objects/room.hpp
    include/objects/item.hpp
    include/objects/item_storage.hpp
    include/directions.hpp
    include/commands/look.hpp
    include/commands/icommand.hpp
    include/commands/inventory.hpp
    include/commands/walk.hpp
    include/commands/help.hpp
    include/commands/take.hpp
    include/interpreter.hpp
    include/util/hpta_strings.hpp

)

target_include_directories(${PROJECT_NAME} PUBLIC ./include)

target_link_libraries(${PROJECT_NAME} 
    PRIVATE project_options 
            project_warnings
            CONAN_PKG::fmt
            CONAN_PKG::rapidjson
)
