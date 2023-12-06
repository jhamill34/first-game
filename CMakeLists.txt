cmake_minimum_required(VERSION 3.27)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(HelloWorld)
add_executable(HelloWorld main.cpp)

find_package(glfw3 3.3 REQUIRED)
target_link_libraries(HelloWorld glfw)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/glad/include)
target_sources(HelloWorld PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/glad/src/gl.c)

find_package(OpenGL REQUIRED)
target_link_libraries(HelloWorld OpenGL::GL)

