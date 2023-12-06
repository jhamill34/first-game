cmake_minimum_required(VERSION 3.27)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)

set(PROJECT_NAME
	FirstGame
)
set(PROJECT_SOURCE_DIR src)
set(PROJECT_SOURCE 
	${PROJECT_SOURCE_DIR}/main.cpp
)

project(${PROJECT_NAME})
add_executable(${PROJECT_NAME} ${PROJECT_SOURCE})

find_package(glfw3 3.3 REQUIRED)
target_link_libraries(${PROJECT_NAME} glfw)

add_subdirectory(libs/glad)
target_link_libraries(${PROJECT_NAME} glad)

