project(hpta-app CXX)

add_executable(${PROJECT_NAME}
    main.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC .)

target_link_libraries(${PROJECT_NAME} 
    PRIVATE project_options 
            project_warnings
            hpta-lib
)