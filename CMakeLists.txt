cmake_minimum_required(VERSION 3.27)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)

project(Games)

add_subdirectory(apps/firstGame)
add_subdirectory(libs/glad)

