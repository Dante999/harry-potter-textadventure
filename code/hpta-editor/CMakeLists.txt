project(hpta-editor CXX)

add_executable(${PROJECT_NAME}
	src/main.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC .)

target_link_libraries(${PROJECT_NAME} 
    PRIVATE project_options
            project_warnings
            hpta-lib
			CONAN_PKG::imgui-sfml
)
