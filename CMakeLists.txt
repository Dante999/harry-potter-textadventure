cmake_minimum_required(VERSION 3.15)

project(hpta CXX)


option(CPP_STARTER_USE_IMGUI "Enable compilation of ImGui sample" ON)

# Link this 'library' to set the c++ standard / compile-time options requested
add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_17)

# standard compiler warnings
add_library(project_warnings INTERFACE)
include(cmake/compiler-warnings.cmake)
set_project_warnings(project_warnings)

include(cmake/standard-project-settings.cmake)


include(cmake/conan.cmake)

set(CMAKE_EXPORT_COMPILE_COMMANDS true)

# set(CONAN_EXTRA_REQUIRES ${CONAN_EXTRA_REQUIRES} 
#     fmt/6.2.0
#     rapidjson/1.1.0
#     imgui-sfml/2.3@bincrafters/stable
# )
conan_add_remote(NAME bincrafters
                 INDEX 1
                 URL https://bincrafters.jfrog.io/artifactory/api/conan/conan
                 VERIFY_SSL True)



conan_cmake_run(REQUIRES 
	        fmt/8.0.1
                rapidjson/1.1.0
		gtest/cci.20210126
		imgui-sfml/2.5@bincrafters/stable
		spdlog/1.9.2
		docopt.cpp/0.6.3
                BASIC_SETUP CMAKE_TARGETS
                BUILD missing)


add_subdirectory(code/hpta-lib)
add_subdirectory(code/hpta-app)
add_subdirectory(code/hpta-editor)
add_subdirectory(test)
