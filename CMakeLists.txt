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
conan_add_remote(NAME bincrafters
                 INDEX 1
                 URL https://bincrafters.jfrog.io/artifactory/api/conan/conan
                 VERIFY_SSL True)
				 
conan_cmake_run(CONANFILE conanfile.txt  # or relative build/conanfile.txt
                BASIC_SETUP CMAKE_TARGETS
                BUILD missing)

set(CMAKE_EXPORT_COMPILE_COMMANDS true)





add_subdirectory(code/hpta-lib)
add_subdirectory(code/hpta-app)
add_subdirectory(code/hpta-editor)
add_subdirectory(test)
