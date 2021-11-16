cmake_minimum_required(VERSION 3.15)

project(hpta CXX)



# Link this 'library' to set the c++ standard / compile-time options requested
add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_17)



# standard compiler warnings
add_library(project_warnings INTERFACE)
include(cmake/compiler-warnings.cmake)
set_project_warnings(project_warnings)

include(cmake/standard-project-settings.cmake)


include(cmake/conan.cmake)


set(CONAN_EXTRA_REQUIRES ${CONAN_EXTRA_REQUIRES} 
    fmt/6.2.0
    rapidjson/1.1.0
	#imgui-sfml/2.1@bincrafters/stable
)

run_conan()


add_subdirectory(code/hpta-lib)
add_subdirectory(code/hpta-app)
#add_subdirectory(code/hpta-editor)
