project(hpta-editor CXX)

add_executable(${PROJECT_NAME}
	src/main.cpp
	src/panel_room_attributes.cpp
	src/panel_room_list.cpp
	src/panel_item_list.cpp
	src/map.cpp
	src/room_list.cpp
	src/object_cache.cpp
	include/hpta-editor/ipanel.hpp
	include/hpta-editor/panel_room_attributes.hpp
	include/hpta-editor/panel_room_list.hpp
	include/hpta-editor/panel_item_list.hpp
	include/hpta-editor/settings.hpp
	include/hpta-editor/map.hpp
	include/hpta-editor/room_list.hpp
	include/hpta-editor/object_cache.hpp
)

target_include_directories(${PROJECT_NAME} PUBLIC ./include)

target_link_libraries(${PROJECT_NAME} 
	PRIVATE project_options
	        project_warnings
		hpta-lib
		CONAN_PKG::imgui-sfml
		CONAN_PKG::fmt
		CONAN_PKG::spdlog
		CONAN_PKG::docopt.cpp
)
