cmake_minimum_required(VERSION 3.3)
project(GAME)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

find_package(SDL2 REQUIRED)
#find_package(SDL2_image REQUIRED)
#find_package(SDL2_ttf REQUIRED)

set(SOURCE_FILES main.cpp)
include_directories(${SDL2_INCLUDE_DIR})
#        ${SDL2_IMAGE_INCLUDE_DIR}
#        ${SDL2_TTF_INCLUDE_DIR})

add_executable(GAME ${SOURCE_FILES})
target_link_libraries(GAME ${SDL2_LIBRARY})
#        ${SDL2_IMAGE_LIBRARIES}
#        ${SDL2_TTF_LIBRARIES})

#project(c_sdl)
#
#set(CMAKE_CXX_STANDARD 14)
#
#find_file(SDL2_INCLUDE_DIR NAME SDL.h HINTS SDL2)
#find_library(SDL2_LIBRARY NAME SDL2)
#
#set(SOURCE_FILES main.cpp source/)
##add_subdirectory(source/)
#add_executable(c_sdl main.cpp)
#
##target_include_directories(c_sdl ${SDL2_INCLUDE_DIR})
#target_link_libraries(c_sdl source/ ${SDL2_LIBRARY})