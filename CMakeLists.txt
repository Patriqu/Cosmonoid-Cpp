cmake_minimum_required(VERSION 3.10.2)

project(Cosmonoid2D VERSION 0.57)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED On)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED On)

file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp ${PROJECT_SOURCE_DIR}/src/*/*.cpp ${PROJECT_SOURCE_DIR}/src/*.c main.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})

set(LIB_DIR lib/vs)
set(SDL2_CMAKE_DIR cmake/SDL2)
set(SDL2_INCLUDE_DIR include/SDL2)
set(SDL2_DIR ${LIB_DIR}/${SDL2_CMAKE_DIR})

list(APPEND CMAKE_MODULE_PATH include/SDL2/SDL_config.h)
find_package(SDL2 REQUIRED)

target_include_directories(${PROJECT_NAME} PRIVATE include)
target_include_directories(${PROJECT_NAME} PUBLIC ${SDL2_INCLUDE_DIR})

target_link_directories(${PROJECT_NAME} PUBLIC ${LIB_DIR})
target_link_libraries(${PROJECT_NAME} SDL2 SDL2main SDL2test SDL2_image SDL2_ttf SDL2_mixer winmm)

file(GLOB CONFIG_FILES ${CMAKE_SOURCE_DIR}/config/*.xml)
file(COPY ${CONFIG_FILES} DESTINATION config/)

file(GLOB IMG_FILES ${CMAKE_SOURCE_DIR}/img/*.png)
file(COPY ${IMG_FILES} DESTINATION img/)

file(GLOB SOUND_FILES ${CMAKE_SOURCE_DIR}/sound/*)
file(COPY ${SOUND_FILES} DESTINATION sound/)

file(GLOB TTF_FILES ${CMAKE_SOURCE_DIR}/*.ttf)
file(COPY ${TTF_FILES} DESTINATION /)

file(GLOB DLL_FILES ${CMAKE_SOURCE_DIR}/${LIB_DIR}/*.dll)
file(COPY ${DLL_FILES} DESTINATION /)

set(CPACK_INSTALL_CMAKE_PROJECTS "debug;${PROJECT_NAME};ALL;/" "release;${PROJECT_NAME};ALL;/")