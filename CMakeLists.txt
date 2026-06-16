cmake_minimum_required(VERSION 3.13)

project(shell-starter-cpp)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE SOURCE_FILES src/*.cpp src/*.hpp)

set(CMAKE_CXX_STANDARD 23) # Enable the C++23 standard

add_executable(shell ${SOURCE_FILES})

target_include_directories(shell PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/parser
    ${CMAKE_CURRENT_SOURCE_DIR}/src/fileHandler
    ${CMAKE_CURRENT_SOURCE_DIR}/src/commandMap
    ${CMAKE_CURRENT_SOURCE_DIR}/src/commands
    ${CMAKE_CURRENT_SOURCE_DIR}/src/commands/cd
    ${CMAKE_CURRENT_SOURCE_DIR}/src/commands/type
    ${CMAKE_CURRENT_SOURCE_DIR}/src/commands/echo
    ${CMAKE_CURRENT_SOURCE_DIR}/src/commands/pwd
)

target_link_libraries(shell PRIVATE readline)

