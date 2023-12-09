cmake_minimum_required(VERSION 3.27)

set(PROJECT_NAME
	FirstGameApp
)
set(PROJECT_SOURCE_DIR src)
file(GLOB_RECURSE PROJECT_SOURCE ${PROJECT_SOURCE_DIR}/*.cpp)

set(PROJECT_HEADERS include)
file(GLOB_RECURSE PROJECT_HEADER ${PROJECT_HEADERS}/*.h)

project(${PROJECT_NAME})
add_executable(${PROJECT_NAME} ${PROJECT_SOURCE})
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_HEADERS})


set( GLFW_BUILD_DOCS OFF CACHE BOOL  "GLFW lib only" )
set( GLFW_INSTALL OFF CACHE BOOL  "GLFW lib only" )
target_link_libraries(${PROJECT_NAME} glfw)
target_link_libraries(${PROJECT_NAME} glad)
target_link_libraries(${PROJECT_NAME} glm)
target_link_libraries(${PROJECT_NAME} stb)

