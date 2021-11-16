project(hpta-lib CXX)

add_library(${PROJECT_NAME}
    src/screen.cpp
    src/interpreter.cpp
    src/commands/walk.cpp
    src/commands/help.cpp
    src/commands/look.cpp
    src/services/persistence.cpp
    src/services/gameengine.cpp
    src/services/registry.cpp
    src/visualizer.cpp
    src/persistency/room_persistency.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC ./include)

target_link_libraries(${PROJECT_NAME} 
    PRIVATE project_options 
            project_warnings
            CONAN_PKG::fmt
            CONAN_PKG::rapidjson
)
