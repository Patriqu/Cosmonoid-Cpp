cmake_minimum_required(VERSION 3.10.2)

project(Cosmonoid2D VERSION 0.57)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED On)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED On)

file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp ${PROJECT_SOURCE_DIR}/src/*.c main.cpp)

#list(APPEND CMAKE_MODULE_PATH include/SDL2/SDL_config.h)
#list(APPEND CMAKE_MODULE_PATH include/SDL2/SDL_config.h)

#ADD_DEFINITIONS(-D_AFXDLL)
#SET(CMAKE_MFC_FLAG 2)

#WIN32 
add_executable(${PROJECT_NAME} ${SOURCES})

#set(LIB_X64_DIR lib/mingw/x64)

set(LIB_X64_DIR lib/vs/x64)

set(SDL2_CMAKE_DIR cmake/SDL2)
set(SDL2_INCLUDE_DIR include/SDL2)

set(SDL2_DIR ${LIB_X64_DIR}/${SDL2_CMAKE_DIR})
find_package(SDL2 REQUIRED)

#include_directories(${SDL2_INCLUDE_DIRS})
#include_directories(${SDL2_INCLUDE_DIR})

target_include_directories(${PROJECT_NAME} PRIVATE include)
target_include_directories(${PROJECT_NAME} PUBLIC ${SDL2_INCLUDE_DIR})

#for VERSIONS macros:
target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_BINARY_DIR}")
##

target_link_directories(${PROJECT_NAME} PUBLIC ${LIB_X64_DIR})
#target_link_libraries(${PROJECT_NAME} SDL2 SDL2::Main SDL2test SDL2_image SDL2_ttf SDL2_mixer winmm)
target_link_libraries(${PROJECT_NAME} SDL2 SDL2main SDL2test SDL2_image SDL2_ttf SDL2_mixer winmm)

## copying resource and config files to built executable directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_SOURCE_DIR}/config $<TARGET_FILE_DIR:${PROJECT_NAME}>/config)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_SOURCE_DIR}/img $<TARGET_FILE_DIR:${PROJECT_NAME}>/img)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_SOURCE_DIR}/sound $<TARGET_FILE_DIR:${PROJECT_NAME}>/sound)

## copy ttf
file(GLOB TTF_FILES
     ${CMAKE_SOURCE_DIR}/*.ttf
     )
file(COPY ${TTF_FILES} DESTINATION /)

## copy DLL files to built executable directory
file(GLOB DLL_FILES
     ${CMAKE_SOURCE_DIR}/${LIB_X64_DIR}/*.dll
     )
#file(COPY ${DLL_FILES} DESTINATION Debug)
file(COPY ${DLL_FILES} DESTINATION /)

#add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#COMMAND ${CMAKE_COMMAND} -E copy
#    ${CMAKE_SOURCE_DIR}/lib/vs/x64/*.dll $<TARGET_FILE_DIR:${PROJECT_NAME}>/lib/vs/x64/*.dll)


set(CPACK_INSTALL_CMAKE_PROJECTS
    "debug;${PROJECT_NAME};ALL;/"
    "release;${PROJECT_NAME};ALL;/"
    )