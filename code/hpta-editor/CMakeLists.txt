project(hpta-editor CXX)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/panel_room_attributes.cpp
    src/panel_room_list.cpp
    #src/panel_item_attributes.cpp
    #src/panel_item_list.cpp
    #src/panel_spells.cpp
    src/window_items.cpp
    src/window_spells.cpp
    src/window_rooms.cpp
    src/map.cpp
    src/object_cache.cpp
    src/event_engine.cpp
    src/map_navigation.cpp
    src/hpta_imgui.cpp
)

target_link_libraries(${PROJECT_NAME} 
    PRIVATE project_options
            project_warnings
            hpta-lib
            CONAN_PKG::imgui-sfml
            CONAN_PKG::fmt
            CONAN_PKG::spdlog
            CONAN_PKG::docopt.cpp
)
