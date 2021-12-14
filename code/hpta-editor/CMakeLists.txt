project(hpta-editor CXX)

add_executable(${PROJECT_NAME}
	src/main.cpp
	src/panel_room_attributes.cpp
	src/panel_room_selector.cpp
	src/settings.cpp
	src/map.cpp
	src/room_list.cpp
	include/hpta-editor/panel_room_attributes.hpp
	include/hpta-editor/panel_room_selector.hpp
	include/hpta-editor/settings.hpp
	include/hpta-editor/map.hpp
	include/hpta-editor/room_list.hpp
)

target_include_directories(${PROJECT_NAME} PUBLIC ./include)

target_link_libraries(${PROJECT_NAME} 
	PRIVATE project_options
	        project_warnings
		hpta-lib
		CONAN_PKG::imgui-sfml
		CONAN_PKG::fmt
		CONAN_PKG::spdlog

)
