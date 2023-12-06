cmake_minimum_required(VERSION 3.27)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(HelloWorld)
add_executable(HelloWorld main.cpp)

add_subdirectory(glad)
target_link_libraries(HelloWorld glad)

find_package(glfw3 3.3 REQUIRED)
target_link_libraries(HelloWorld glfw)

