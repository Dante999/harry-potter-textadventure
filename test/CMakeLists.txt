project(unittest)

add_executable(${PROJECT_NAME} test_hpta_utils.cpp)


target_link_libraries(${PROJECT_NAME}
	PRIVATE project_options
	        project_warnings
		CONAN_PKG::gtest
		hpta-lib
)
