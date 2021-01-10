cmake_minimum_required(VERSION 3.10.2)

project(Cosmonoid2D)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED On)

add_executable(${PROJECT_NAME} main.cpp)

set(SDL2_DIR lib/mingw/x64/cmake/SDL2)

find_package(SDL2 REQUIRED)
include_directories(include/SDL2)

target_include_directories(${PROJECT_NAME} PUBLIC include)

target_link_directories(${PROJECT_NAME} PRIVATE lib/vs/x64)

target_link_libraries(${PROJECT_NAME} lib/vs/x64)